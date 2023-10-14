#include "qwinring0Driver.h"
#include <OlsDef.h>
#include <OlsApiInit.h>

QWinRing0Driver::QWinRing0Driver()
{
   bDriverLoad = InitOpenLibSys(&hOpenLibSys);
}

BYTE QWinRing0Driver::readIoPortByte(WORD port)
{
    return ReadIoPortByte(port);
}

WORD QWinRing0Driver::readIoPortWord(WORD port)
{
    return ReadIoPortWord(port);
}

DWORD QWinRing0Driver::readIoPortDWord(WORD port)
{
    return ReadIoPortDword(port);
}

void QWinRing0Driver::writeIoPortByte(WORD port, BYTE value)
{
    WriteIoPortByte(port,value);
}

void QWinRing0Driver::writeIoPortWord(WORD port, WORD value)
{
     WriteIoPortWord(port,value);
}

void QWinRing0Driver::writeIoPortDWord(WORD port, DWORD value)
{
    WriteIoPortDword(port,value);
}

BYTE QWinRing0Driver::readPciConfigByte(DWORD pciAddress, BYTE offset)
{
    return ReadPciConfigByte(pciAddress,offset);
}

WORD QWinRing0Driver::readPciConfigWord(DWORD pciAddress, BYTE offset)
{
    return ReadPciConfigWord(pciAddress,offset);
}

DWORD QWinRing0Driver::readPciConfigDWord(DWORD pciAddress, BYTE offset)
{
    return ReadPciConfigDword(pciAddress,offset);
}

void QWinRing0Driver::writePciConfigByte(DWORD pciAddress, BYTE offset, BYTE value)
{
    WritePciConfigByte(pciAddress,offset,value);
}

void QWinRing0Driver::writePciConfigWord(DWORD pciAddress, BYTE offset, WORD value)
{
    WritePciConfigWord(pciAddress,offset,value);
}

void QWinRing0Driver::writePciConfigDWord(DWORD pciAddress, BYTE offset, DWORD value)
{
    WritePciConfigDword(pciAddress,offset,value);
}

BYTE QWinRing0Driver::pciGetBus(DWORD address)
{
    return (BYTE)((address >> 8) & 0xFF);
}

BYTE QWinRing0Driver::pciGetDev(DWORD address)
{
    return (BYTE)((address >> 3) & 0x1F);
}

BYTE QWinRing0Driver::pciGetFunc(DWORD address)
{
    return (BYTE)(address & 0x07);
}

DWORD QWinRing0Driver::pciBusDevFunc(BYTE bus, BYTE dev, BYTE func)
{
    return PciBusDevFunc(bus, dev, func);
}

DWORD QWinRing0Driver::findPciDeviceByClass(BYTE baseClass, BYTE subClass1,BYTE subClass2)
{
     DWORD pciAddress;
     BYTE gclass,gsclass;
     for (BYTE bus = 0; bus <= gPciNumberOfBus; bus++){
        for (byte dev = 0; dev < gPciNumberOfDevice; dev++){
            for (byte func = 0; func < gPciNumberOfFunction; func++) {

                pciAddress = PciBusDevFunc(bus, dev, func);
                if(ReadPciConfigWord(pciAddress, 0x00) != 0xffff)
                {
                    gclass = ReadPciConfigByte(pciAddress, 0x0B);
                    if(gclass == baseClass){
                        gsclass = ReadPciConfigByte(pciAddress,0x0A);
                        if(gsclass == subClass1 || gsclass == subClass2)
                        {
                          return pciAddress;
                        }
                    }
                }
            }
        }

     }
     return 0;
}



