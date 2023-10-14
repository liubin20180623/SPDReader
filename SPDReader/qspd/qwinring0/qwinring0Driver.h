#ifndef QWINRING0DRIVER_H
#define QWINRING0DRIVER_H
#include <windows.h>

class QWinRing0Driver
{
public:
    static QWinRing0Driver& instance(){
        static QWinRing0Driver instance;
        return instance;
    }

//IO
    BYTE  readIoPortByte(WORD port);
    WORD  readIoPortWord(WORD port);
    DWORD readIoPortDWord(WORD port);

    void writeIoPortByte(WORD port,BYTE value);
    void writeIoPortWord(WORD port,WORD value);
    void writeIoPortDWord(WORD port,DWORD value);

//PCI
    BYTE  readPciConfigByte(DWORD pciAddress,BYTE offset);
    WORD  readPciConfigWord(DWORD pciAddress,BYTE offset);
    DWORD readPciConfigDWord(DWORD pciAddress,BYTE offset);

    void writePciConfigByte(DWORD pciAddress,BYTE offset,BYTE value);
    void writePciConfigWord(DWORD pciAddress,BYTE offset,WORD value);
    void writePciConfigDWord(DWORD pciAddress,BYTE offset,DWORD value);

    BYTE pciGetBus(DWORD address);
    BYTE pciGetDev(DWORD address);
    BYTE pciGetFunc(DWORD address);

    DWORD pciBusDevFunc(BYTE bus,BYTE dev,BYTE func);
    DWORD findPciDeviceByClass(BYTE baseClass, BYTE subClass1,BYTE subClass2);

protected:
    QWinRing0Driver();

private:
    HMODULE     hOpenLibSys;
    BYTE        gPciNumberOfBus         = 255;
    BYTE        gPciNumberOfDevice      = 32;
    BYTE        gPciNumberOfFunction    = 8;

public:
    bool        bDriverLoad             = false;
};

#endif // QWINRING0DRIVER_H
