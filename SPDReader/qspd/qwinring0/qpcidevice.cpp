#include "qpcidevice.h"

QPciDevice::QPciDevice()
    :pciInfo(0,0,0)
{

}

QPciDevice::QPciDevice(BYTE Bus,BYTE Dev,BYTE Func)
    :pciInfo(Bus,Dev,Func)

{

}

QPciDevice::QPciDevice(DWORD memoryAddress)
    :pciInfo(QWinRing0Driver::instance().pciGetBus(memoryAddress),
             QWinRing0Driver::instance().pciGetDev(memoryAddress),
             QWinRing0Driver::instance().pciGetFunc(memoryAddress))
{

}
