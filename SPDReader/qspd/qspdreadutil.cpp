#include "qspdreadutil.h"
#include <QDebug>
#include <QThread>
#include <qconfig.h>
#include <QSettings>
#include <asynclog.h>
#include <spdreadoption.h>

/*
 * ddr4 多了切page的动作。切page的方式是对 0x36 (SPA0) 或 0x37 (SPA1) 的7 bits address写入一个byte (data填0x00就好)。
 * 这个指令对照SMBus Spec 就是Send Byte(*0x36 是7bit address, 要加上一个R/W# bit=0 才会是最后送出的address，所以 0x36 <<1 | 0 = 0x6C)
*/
static BYTE SPA_DDR4[] ={0x6C,0x6E};


QSPDReadUtil &QSPDReadUtil::instance()
{
    static QSPDReadUtil instance;
    return instance;
}

VMSpdData QSPDReadUtil::read()
{
   VMSpdData v_mSpdData;
   BYTE addr,data;

   do
   {
       if(!m_smbus.isInitSuccess())
       {
           break;
       }

       for(addr = 0xA0; addr < 0xAf; addr+=2)
       {
         data = m_smbus.readSlaveData(addr,0);
//       aInfo() << QString("DDR Addr:0x%1 0x%2").arg(addr,2,16,QLatin1Char('0')).arg(data,2,16,QLatin1Char('0'));

           if(data !=0xff)
           {
               MSpdData mspdData;
               for(BYTE page = 0; page < pageNO();page++)
               {
                   switchPage(addr,page);
                   QThread::msleep(10);

                   for(int row = 0; row < rowSize();row++)
                   {
                       QVector<std::tuple<QString,bool>> rowData;
                       for(int column = 0; column < 16; column++)
                       {
                          BYTE columnData        =  m_smbus.readSlaveData(addr,convertOffset(row * 16 + column));
                          QString strcolumnData  =  QString("%1").arg(columnData,2,16,QLatin1Char('0')).toUpper();
                          rowData.push_back(std::make_tuple(strcolumnData,false));
                       }

                       WORD rowKey          = row * 16 + pageSize()*page;
                       QString strRowKey    = QString("%1").arg(rowKey,3,16,QLatin1Char('0')).toUpper() ;
                       mspdData[strRowKey]  = rowData;
                   }

               }
               v_mSpdData.push_back(mspdData);
           }
       }

   }while(false);

   return v_mSpdData;
}

BYTE QSPDReadUtil::convertOffset(BYTE offset)
{
    if(g_spdread_options->m_type == DDR4)
        return offset;
    else if(g_spdread_options->m_type == DDR5)
        return (0x80|offset);

    return 0;
}

int QSPDReadUtil::rowSize()
{
    if(g_spdread_options->m_type == DDR4)
        return 16;
    else if(g_spdread_options->m_type == DDR5)
        return 8;

    return 0;
}

int QSPDReadUtil::pageNO()
{
    if(g_spdread_options->m_type == DDR4)
        return 2;
    else if(g_spdread_options->m_type == DDR5)
        return 8;

    return 0;
}

int QSPDReadUtil::pageSize()
{
    if(g_spdread_options->m_type == DDR4)
        return 256;
    else if(g_spdread_options->m_type == DDR5)
        return 128;

    return 0;
}

bool QSPDReadUtil::switchPage(BYTE slave_address,BYTE page)
{
    if(g_spdread_options->m_type == DDR4)
        return m_smbus.writeSlaveData(SPA_DDR4[page],0x00,0x00);
    else if(g_spdread_options->m_type == DDR5)
         return m_smbus.writeSlaveData(slave_address,0x0B,page);

    return false;
}


