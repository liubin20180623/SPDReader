#include "qspdreader.h"
#include <OlsDef.h>
#include <OlsApiInit.h>

#include <QDebug>

#define BIT0				1
#define BIT1				2

#define NVIDIA_SMB_PRTCL	0x00       /* protocol, PEC */
#define NVIDIA_SMB_STS		0x01       /* status */
#define NVIDIA_SMB_ADDR		0x02       /* address */
#define NVIDIA_SMB_CMD		0x03       /* command */
#define NVIDIA_SMB_DATA		0x04       /* 32 data registers */
#define NVIDIA_SMB_BCNT		0x24       /* number of data bytes */
#define NVIDIA_SMB_ALRM_A	0x25       /* alarm address */
#define NVIDIA_SMB_ALRM_D	0x26       /* 2 bytes alarm data */

#define NVIDIA_SMB_STS_DONE	0x80
#define NVIDIA_SMB_STS_ALRM	0x40
#define NVIDIA_SMB_STS_RES	0x20
#define NVIDIA_SMB_STS_STATUS	0x1f

#define NVIDIA_SMB_PRTCL_WRITE	0x00
#define NVIDIA_SMB_PRTCL_READ	0x01
#define NVIDIA_SMB_PRTCL_QUICK	0x02
#define NVIDIA_SMB_PRTCL_BYTE	0x04
#define NVIDIA_SMB_PRTCL_BYTE_DATA	0x06
#define NVIDIA_SMB_PRTCL_WORD_DATA	0x08
#define NVIDIA_SMB_PRTCL_BLOCK_DATA	0x0a
#define NVIDIA_SMB_PRTCL_PROC_CALL	0x0c
#define NVIDIA_SMB_PRTCL_BLOCK_PROC_CALL	0x0d
#define NVIDIA_SMB_PRTCL_I2C_BLOCK_DATA		0x4a
#define NVIDIA_SMB_PRTCL_PEC	0x80

#define MAX_TIMEOUT 1000

#define SMBHSTSTS	0x0    // smbus host status register
#define SMBHSTCNT	0x2    // smbus host control register
#define SMBHSTCMD	0x3    // smbus host command register
#define SMBHSTADD	0x4    // smbus host address register
#define SMBHSTDAT0	0x5    // smbus host data 0 register
#define SMBHSTDAT1	0x6    // smbus host data 1 register
#define SMBBLKDAT	0x7    // smbus block data register

void delay1us(DWORD delay)
{
    LARGE_INTEGER start,end,Freq;

    QueryPerformanceFrequency(&Freq);
    //end.QuadPart = (delay*Freq.QuadPart)/1000;        //1ms
    end.QuadPart = (delay*Freq.QuadPart)/1000000;        //1us
    QueryPerformanceCounter(&start);
    end.QuadPart = end.QuadPart+start.QuadPart;/*-System_test()*2;*/
    do
    {
        QueryPerformanceCounter(&Freq);
    }while (Freq.QuadPart<=end.QuadPart);
}

QSPDReader::QSPDReader()
    :m_hOpenLibSys(NULL)
    ,SMB_base(0)
    ,smb_type(-1)
{
   InitOpenLibSys(&m_hOpenLibSys);
}

QSPDReader::~QSPDReader()
{
   DeinitOpenLibSys(&m_hOpenLibSys);
}


bool QSPDReader::searchDevice(BYTE Classtype,BYTE Subclass1,BYTE Subclass2,WORD *vd,BYTE *Bus, BYTE *Dev, BYTE *Func)
{
    WORD i;
    WORD vendor,dvc;
    BYTE gclass,gsclass,j,k;
    DWORD address;
    for(i = 0; i < 256; i++)
    {
        for(j = 0; j < 32; j++)
        {
            for(k = 0; k < 8; k++)
            {
                // Bus Number, Device Number and Function Number to PCI Device Address
                address = PciBusDevFunc(i, j, k);
                if(k == 0)
                {

                }
                // read a word from the specified PCI config address
                vendor = ReadPciConfigWord(address, 0x00);
                if(vendor != 0xffff)//If vendor is valid
                {
                    dvc = ReadPciConfigWord(address, 0x02);
                    gclass = ReadPciConfigByte(address, 0x0B);
                    qDebug() << gclass << Classtype;

                    if(1)
                    {
                       gsclass = ReadPciConfigByte(address,0x0A);
                       if(gsclass == Subclass1 || gsclass == Subclass2)
                       {
                           *Bus = (BYTE)i;
                           *Dev = (BYTE)j;
                           *Func = (BYTE)k;
                           *vd = vendor;
                           if(vendor == 0x10de)
                           {
                               if(dvc == 0x52)
                               {
                                  // SMB_base = ReadPciConfigWord(address,0x50);
                                  // SMB_base &= 0xfffe;
                               }
                           }
                           else if(vendor == 0x8086)
                           {
                              SMB_base = ReadPciConfigWord(address,0x20);
                              //SMB_base &= 0xfffe;
                           }
                           else
                           {
                               return 0;
                           }
                           return 1;
                       }
                    }
                }
                /*
                if(k == 0 && tp != 0x80)
                {
                   break;
                }
                */
            }//end of for(k = 0; k < 8; k++)
        }//end of for(j = 0; j < 32; j++)
    }//end of for(i = 0; i < 256; i++)
    return 0;
}

BYTE QSPDReader::readSlaveData(BYTE slave_address, WORD offset)
{
    if(smb_type == 0)
    {
       return readAMDSlaveData(slave_address,offset);
    }
    return readIntelSlaveData(slave_address,offset);
}

bool QSPDReader::switchPage_ddr4(BYTE page)
{
    /*
     * ddr4 多了切page的动作。切page的方式是对 0x36 (SPA0) 或 0x37 (SPA1) 的7 bits address写入一个byte (data填0x00就好)。
     * 这个指令对照SMBus Spec 就是Send Byte(*0x36 是7bit address, 要加上一个R/W# bit=0 才会是最后送出的address，所以 0x36 <<1 | 0 = 0x6C)
    */
    static BYTE SPA_DDR4[] ={0x6C,0x6E};

    if(page <0 || page >=2)
        return false;

    return writeSlaveData(SPA_DDR4[page],0x00,0x00);
}

bool QSPDReader::switchPage_ddr5(BYTE slave_address, WORD offset, BYTE page)
{
    /*
     *SPD5 支持两种地址模式， 1byte 和2bytes 模式. 這裡我用的是1byte模式，即每讀取128 byte，需修改MR11 2:0  切換到下一個PAGE.
     * offset -> MR11 0x0B
     * page -> 0 ~7
     */
    return writeSlaveData(slave_address,offset,page);
}

bool QSPDReader::writeSlaveData(BYTE slave_address, WORD offset,BYTE data)
{
    BYTE temp;
    int timeout=0;
    bool Status;
    BYTE Data8 = 0, RetryCycles = 5, i = 0;

    for (i = 0; i < RetryCycles; i++)
    {
        WriteIoPortByte((SMBHSTSTS + SMB_base),0x1E);

        if (Data8 == 0xFF)
        {
            Data8 = ReadIoPortByte(SMB_base + SMBHSTCNT);
            if (Data8 == 0xFF)
                return  false;
        }

        //Host Status Register SMB_BASE + 00h
        //bit0 = 0 , SMBUS is idle, bit0 = 1, SMBUS is busy
        do {
            Data8 = ReadIoPortByte(SMB_base + SMBHSTSTS);
            WriteIoPortByte((SMBHSTSTS + SMB_base),Data8);

        } while ((Data8 & BIT0) != 0);

        //for write
       // WriteIoPortByte((SMBHSTADD + SMB_base),slave_address& 0xFE);

        WriteIoPortByte((SMBHSTADD + SMB_base),(BYTE)(slave_address|1));

        delay1us(10);//delay

        //set command byte in the HST_CMD register (SMBBase + 0x03)
        WriteIoPortByte((SMBHSTCMD + SMB_base),offset);
        delay1us(10);//delay


        //Host Data 0 register  is as a data register to write/read in byte/word mode
        WriteIoPortByte((SMBHSTDAT0 + SMB_base),data);
        delay1us(10);//delay

        //set control register to 0x48
        WriteIoPortByte((SMBHSTCNT + SMB_base),0x50);
        Status = true;

        delay1us(10);//delay

        do {
             delay1us(10);//delay

            Data8 = ReadIoPortByte(SMB_base + SMBHSTSTS);
            //get the value here is 0x44,
            if ((Data8 & 0x04) != 0)
            {
                //bit 3 BUS_ERR
                //delay
                Status = false;
                break;
            }
        } while ((Data8 & BIT1) != 0x2);//((Data8&0x01)!=0x01);

        WriteIoPortByte((SMBHSTSTS + SMB_base),ReadIoPortByte(SMB_base + SMBHSTSTS)); //Host Status Register ;clear status

        if (Status == true)
            return Status;
    }

    return Status;
}

bool QSPDReader::switchPage(BYTE slave_address, WORD offset, BYTE page)
{
    if(ddr_type == DDR4){
      return switchPage_ddr4(page);
    }else if(ddr_type == DDR5){
       return switchPage_ddr5(slave_address,offset,page);
    }
    return false;
}

BYTE QSPDReader::readIntelSlaveData(BYTE slave_address, WORD offset)
{
    BYTE temp;
    int timeout=0;
    //clear all status bits
    WriteIoPortByte((SMBHSTSTS + SMB_base),0x1E);

    // write the offset
//    WriteIoPortByte((SMBHSTCMD + SMB_base),(BYTE)((0x80|offset)));

    WriteIoPortByte((SMBHSTCMD + SMB_base),(BYTE)((offset)));

    // write the slave address
    WriteIoPortByte((SMBHSTADD + SMB_base),(BYTE)(slave_address|1));

    //Read byte protocol and Start
    WriteIoPortByte((SMBHSTCNT + SMB_base),0x48);

    while(1)
    {
       delay1us(10);
       temp = ReadIoPortByte(SMB_base + SMBHSTSTS);
       if((temp & 0x42)==0x42)
       {
          break;
       }
       timeout++;

       if(timeout > MAX_TIMEOUT)
       {
           return 0xff;
       }

    }

    if((temp & 0x1c)==0)
    {//ok
       temp = ReadIoPortByte(SMBHSTDAT0 + SMB_base);
       return temp;
    }
    return 0xff;

}

BYTE QSPDReader::readAMDSlaveData(BYTE slave_address, WORD offset)
{
    BYTE temp,tmp;//protocol,
    int timeout = 0;

    // for AMD
     WriteIoPortByte((SMB_base+NVIDIA_SMB_STS),NVIDIA_SMB_STS_STATUS);

     //I2C_SMBUS_BYTE_DATA:
     WriteIoPortByte((SMB_base+NVIDIA_SMB_CMD),offset);

     WriteIoPortByte((SMB_base+NVIDIA_SMB_ADDR),(BYTE)(slave_address|0x01));

     WriteIoPortByte((SMB_base+NVIDIA_SMB_PRTCL),0x07);

     do{
         delay1us(10);
         temp = ReadIoPortByte(SMB_base + NVIDIA_SMB_STS);

     } while (((temp & NVIDIA_SMB_STS_DONE) == 0) && (timeout++ < MAX_TIMEOUT));

     if(timeout > MAX_TIMEOUT)
     {
         return 0xff;
     }

    tmp = ReadIoPortByte(SMB_base+NVIDIA_SMB_DATA);

    return tmp;
}

bool QSPDReader::isValidChip(const WORD& vendor)
{
    if(vendor == 0x10DE)
    {
       smb_type = 0;
       return true;
    }
    else if(vendor == 0x8086)
    {
       smb_type = 1;
       return true;
    }
    return false;
}



