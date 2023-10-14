#include "qsmbus.h"
#include <qpcidevice.h>
#include <qioport.h>
#include <asynclog.h>

#define BIT0				1
#define BIT1				2

#define MAX_TIMEOUT         1000

#define SMBHSTSTS           0x0    // smbus host status register
#define SMBHSTCNT           0x2    // smbus host control register
#define SMBHSTCMD           0x3    // smbus host command register
#define SMBHSTADD           0x4    // smbus host address register
#define SMBHSTDAT0          0x5    // smbus host data 0 register
#define SMBHSTDAT1          0x6    // smbus host data 1 register
#define SMBBLKDAT           0x7    // smbus block data register

void delay1us(DWORD delay)
{
    LARGE_INTEGER start,end,Freq;

    QueryPerformanceFrequency(&Freq);
    //end.QuadPart = (delay*Freq.QuadPart)/1000;        //1ms
    end.QuadPart = (delay*Freq.QuadPart)/1000000;       //1us
    QueryPerformanceCounter(&start);
    end.QuadPart = end.QuadPart+start.QuadPart;/*-System_test()*2;*/
    do
    {
        QueryPerformanceCounter(&Freq);
    }while (Freq.QuadPart<=end.QuadPart);
}

QSmbus::QSmbus()
    :pQPciDevice(nullptr)
    ,pQIOPort(nullptr)
{
   bInitSuccess = initialize();
   aInfo() << QString("SMbus Base:0x%1").arg(SMB_base,4,16,QLatin1Char('0'));
   if(bInitSuccess){
      pQIOPort = new QIOPort(SMB_base);
   }
}

bool QSmbus::initialize()
{
    if(!QWinRing0Driver::instance().bDriverLoad){
        aInfo() << QString("WinRing0 Loading Fail");
        return false;
    }
    device_info = getDeviceInfo();

    switch(device_info.vendorId)
    {
         case VendorId::Intel:{
            DWORD  smbus = QWinRing0Driver::instance().findPciDeviceByClass(QPciDevice::Serial,QPciDevice::Smbus,QPciDevice::Smbus);
            if(smbus >0){
                   pQPciDevice  = new QPciDevice(smbus);
                   SMB_base     = pQPciDevice->read<WORD>(QPciDevice::BaseAddress);
                   SMB_base     &= 0xfffe;
                   return true;
             }
        }
        break;

        case VendorId::AMD:{

            const WORD SMB_IDX = 0xCD6;
            const WORD SMB_DAT = 0xCD7;
            const byte smb_en  = 0x00;

            QWinRing0Driver::instance().writeIoPortByte(SMB_IDX, smb_en);
            byte smba_en_lo = QWinRing0Driver::instance().readIoPortByte(SMB_DAT);
            QWinRing0Driver::instance().writeIoPortByte(SMB_IDX, smb_en+1);
            byte smba_en_hi = QWinRing0Driver::instance().readIoPortByte(SMB_DAT);

            if(smba_en_hi == 0xff || smba_en_lo == 0xff)
            {
               //Mmio 0xFED80300
               //PMIO is disabled, AMD SMBus controllers have two adapters with fixed I/O spaces at 0x0B00 and 0x0B20
                SMB_base = 0x0B00;
            }
            else
            {
                WORD SMBusPort = 0x00;
                SMBusPort |= smba_en_hi << 8;
                SMB_base = SMBusPort;
            }
            return true;
         }
         break;
    }

    return false;
}

QSmbus::DeviceInfo QSmbus::getDeviceInfo()
{
    DeviceInfo result;
    QPciDevice* platform =  new QPciDevice();
    result.vendorId = (VendorId)platform->vendorId();

    switch (result.vendorId) {
        case VendorId::Intel:
            break;

        case VendorId::AMD:
             break;
    }

    return result;
}

bool QSmbus::writeSlaveData(BYTE slave_address, WORD offset, BYTE data)
{
    bool Status;
    BYTE Data8 = 0, RetryCycles = 5, i = 0;

    for (i = 0; i < RetryCycles; i++)
    {
        pQIOPort->write<BYTE>((SMBHSTSTS),0x1E);

        if (Data8 == 0xFF)
        {
            Data8 = pQIOPort->read<BYTE>(SMBHSTCNT);

            if (Data8 == 0xFF)
                return  false;
        }

        //Host Status Register SMB_BASE + 00h
        //bit0 = 0 , SMBUS is idle, bit0 = 1, SMBUS is busy
        do {
            Data8 = pQIOPort->read<BYTE>(SMBHSTSTS);
            pQIOPort->write<BYTE>(SMBHSTSTS,Data8);

        } while ((Data8 & BIT0) != 0);

        //for write
        //for intel slave_address|1
        //for AMD slave_address & 0xFE
        switch(device_info.vendorId)
        {
            case VendorId::Intel:
              pQIOPort->write<BYTE>(SMBHSTADD,(BYTE)(slave_address|1));
                break;

            case VendorId::AMD:
              pQIOPort->write<BYTE>(SMBHSTADD,(BYTE)(slave_address & 0xFE));
                 break;
        }
        delay1us(1);

        //set command byte in the HST_CMD register
        pQIOPort->write<BYTE>(SMBHSTCMD,offset);
        delay1us(1);

        //Host Data 0 register  is as a data register to write/read in byte/word mode
        pQIOPort->write<BYTE>(SMBHSTDAT0,data);
        delay1us(1);

        //set control register to 0x50
        pQIOPort->write<BYTE>(SMBHSTCNT,0x50);
        Status = true;

        do {
             delay1us(1);
            Data8 = pQIOPort->read<BYTE>(SMBHSTSTS);
            if ((Data8 & 0x04) != 0)
            {
                //bit 3 BUS_ERR
                Status = false;
                break;
            }
        } while ((Data8 & BIT1) != 0x2);//((Data8&0x01)!=0x01);

        //Host Status Register ;clear status
        pQIOPort->write<BYTE>(SMBHSTSTS,pQIOPort->read<BYTE>(SMBHSTSTS));

        if (Status == true)
            return Status;
    }

    return Status;
}

BYTE QSmbus::readSlaveData(BYTE slave_address, WORD offset)
{
    BYTE Data8;
    bool Status;

    //clear all status bits
    pQIOPort->write<BYTE>(SMBHSTSTS,0x1E);

    Data8 = pQIOPort->read<BYTE>(SMBHSTSTS);
    if (Data8 == 0xFF)
    {
        Data8 = pQIOPort->read<BYTE>(SMBHSTCNT);

        if (Data8 == 0xFF)
             return  0xff;
    }

    //Host Status Register SMB_BASE + 00h
    //bit0 = 0 , SMBUS is idle, bit0 = 1, SMBUS is busy
    do {
        Data8 = pQIOPort->read<BYTE>(SMBHSTSTS);
        pQIOPort->write<BYTE>(SMBHSTSTS,Data8);

    } while ((Data8 & BIT0) != 0);

    // write the slave address
    pQIOPort->write<BYTE>(SMBHSTADD,(BYTE)(slave_address|1));
    delay1us(1);

    //write the offset
    pQIOPort->write<BYTE>(SMBHSTCMD,(BYTE)((offset)));
    delay1us(1);

    //Read byte protocol and Start
    pQIOPort->write<BYTE>(SMBHSTCNT,0x48);
    delay1us(1);

    Status = true;

    do {
        Data8 = pQIOPort->read<BYTE>(SMBHSTSTS);
        if ((Data8 & 0x04) != 0)
        {
            Status = false;
            break;
        }
        delay1us(1);

    } while ((Data8 & BIT1) != 0x2);

    delay1us(1);
    if(Status == true){
         Data8 = pQIOPort->read<BYTE>(SMBHSTDAT0);
         return Data8;
    }

    return 0xff;
}

