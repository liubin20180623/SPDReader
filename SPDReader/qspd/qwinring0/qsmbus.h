#ifndef QSMBUS_H
#define QSMBUS_H

#include <QObject>
#include <qwinring0Driver.h>

class QPciDevice;
class QIOPort;
class QSmbus
{
public:
    enum VendorId {
       Intel         = 0x8086,
       AMD           = 0x1022,
    };

    struct DeviceInfo{
        VendorId vendorId;
    };

    QSmbus();

    bool initialize();
    bool isInitSuccess(){return bInitSuccess;}
    DeviceInfo getDeviceInfo();

    bool writeSlaveData(BYTE slave_address, WORD offset,BYTE data);
    BYTE readSlaveData(BYTE slave_address, WORD offset);

private:
    QPciDevice* pQPciDevice;
    QIOPort* pQIOPort;

    DeviceInfo device_info;
    WORD SMB_base;
    bool bInitSuccess = false;
};

#endif // QSMBUS_H
