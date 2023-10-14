#ifndef QSPDREADER_H
#define QSPDREADER_H

#include <windows.h>

class QSPDReader
{
    enum DRAM
    {
      DDR4  = 1,
      DDR5  = 2
    };

public:
    QSPDReader();
    ~QSPDReader();

public:
    bool searchDevice(BYTE Classtype,BYTE Subclass1,BYTE Subclass2,WORD *vd,BYTE *Bus, BYTE *Dev, BYTE *Func);
    BYTE readSlaveData(BYTE slave_address, WORD offset);
    bool writeSlaveData(BYTE slave_address, WORD offset,BYTE data);
    bool switchPage(BYTE slave_address, WORD offset,BYTE page);
    bool isValidChip(const WORD& vendor);

private:
    bool switchPage_ddr4(BYTE page);
    bool switchPage_ddr5(BYTE slave_address, WORD offset,BYTE page);
    BYTE readIntelSlaveData(BYTE slave_address, WORD offset);
    BYTE readAMDSlaveData(BYTE slave_address, WORD offset);

public:
    HMODULE m_hOpenLibSys;
    WORD SMB_base;
    int smb_type;
    DRAM ddr_type = DDR4;
};

#endif // QSPDREADER_H
