#ifndef QPCIDEVICE_H
#define QPCIDEVICE_H
#include <QObject>
#include <qwinring0Driver.h>

class QPciDevice
{
public:
    enum BaseClass{
        Bridge               = 0x06,
        Serial               = 0x0C
    };

    enum SubClass{
        Isa                  = 0x01,
        Smbus                = 0x05
    };

    enum RegisterOffset{
        VendorId              = 0x00,
        DeviceId              = 0x02,
        Status                = 0x06,
        RevisionId            = 0x08,
        SubType               = 0x0A,
        BaseType              = 0x0B,
        BaseAddress           = 0x20,
        SubsystemId           = 0x2E,
        SubsystemVendorId     = 0x2C
    };

    struct PciInfo{
         BYTE BusNumber;
         BYTE DeviceNumber;
         BYTE FunctionNumber;
         DWORD DeviceMemoryLocation;

         PciInfo(BYTE Bus,BYTE Dev,BYTE Func)
         {
             this->BusNumber             = Bus;
             this->DeviceNumber          = Dev;
             this->FunctionNumber        = Func;
             this->DeviceMemoryLocation  = QWinRing0Driver::instance().pciBusDevFunc(Bus,Dev,Func);
         };

     }pciInfo;

    QPciDevice();
    QPciDevice(BYTE Bus,BYTE Dev,BYTE Func);
    QPciDevice(DWORD memoryAddress);

    inline WORD vendorId(){
        return read<WORD>(VendorId);
    };
    inline WORD deviceId(){
        return read<WORD>(DeviceId);
    };
    inline WORD revisionId(){
        return read<WORD>(RevisionId);
    };

    template<class T>
    T read(BYTE offset);

    template<class T>
    void write(BYTE offset, T value);
};

template<class T>
T QPciDevice::read(BYTE offset)
{
    T data = 0;
    DWORD location = pciInfo.DeviceMemoryLocation;

    if(typeid(T) == typeid(BYTE))
    {
      data = QWinRing0Driver::instance().readPciConfigByte(location,offset);
    }
    else if(typeid(T) == typeid(WORD))
    {
      data = QWinRing0Driver::instance().readPciConfigWord(location,offset);
    }
    else if(typeid(T) == typeid(DWORD))
    {
      data = QWinRing0Driver::instance().readPciConfigDWord(location,offset);
    }

    return data;
}

template<class T>
void QPciDevice::write(BYTE offset, T value)
{
    DWORD location = pciInfo.DeviceMemoryLocation;

    if(typeid(T) == typeid(BYTE))
    {
      QWinRing0Driver::instance().writePciConfigByte(location,offset,value);
    }
    else if(typeid(T) == typeid(WORD))
    {
      QWinRing0Driver::instance().writePciConfigWord(location,offset,value);
    }
    else if(typeid(T) == typeid(DWORD))
    {
      QWinRing0Driver::instance().writePciConfigDWord(location,offset,value);
    }
}

#endif // QPCIDEVICE_H
