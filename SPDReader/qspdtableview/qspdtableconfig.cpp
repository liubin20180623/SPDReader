#include "qspdtableconfig.h"

QStringList QSPDTableConfig::s_HorizontalHeader;
QStringList QSPDTableConfig::s_VerticalHeader;

QStringList QSPDTableConfig::getHorizontalHeader()
{
    if(s_HorizontalHeader.isEmpty())
    {
        s_HorizontalHeader << "";
        s_HorizontalHeader << "00";
        s_HorizontalHeader << "01";
        s_HorizontalHeader << "02";
        s_HorizontalHeader << "03";
        s_HorizontalHeader << "04";
        s_HorizontalHeader << "05";
        s_HorizontalHeader << "06";
        s_HorizontalHeader << "07";
        s_HorizontalHeader << "08";
        s_HorizontalHeader << "09";
        s_HorizontalHeader << "0A";
        s_HorizontalHeader << "0B";
        s_HorizontalHeader << "0C";
        s_HorizontalHeader << "0D";
        s_HorizontalHeader << "0E";
        s_HorizontalHeader << "0F";
    }
    return s_HorizontalHeader;
}

QStringList QSPDTableConfig::getVerticalHeader()
{
   if(s_VerticalHeader.isEmpty())
   {
        s_VerticalHeader << "000";
        s_VerticalHeader << "010";
        s_VerticalHeader << "020";
        s_VerticalHeader << "030";
        s_VerticalHeader << "040";
        s_VerticalHeader << "050";
        s_VerticalHeader << "060";
        s_VerticalHeader << "070";
        s_VerticalHeader << "080";
        s_VerticalHeader << "090";
        s_VerticalHeader << "0A0";
        s_VerticalHeader << "0B0";
        s_VerticalHeader << "0C0";
        s_VerticalHeader << "0D0";
        s_VerticalHeader << "0E0";
        s_VerticalHeader << "0F0";

        s_VerticalHeader << "100";
        s_VerticalHeader << "110";
        s_VerticalHeader << "120";
        s_VerticalHeader << "130";
        s_VerticalHeader << "140";
        s_VerticalHeader << "150";
        s_VerticalHeader << "160";
        s_VerticalHeader << "170";
        s_VerticalHeader << "180";
        s_VerticalHeader << "190";
        s_VerticalHeader << "1A0";
        s_VerticalHeader << "1B0";
        s_VerticalHeader << "1C0";
        s_VerticalHeader << "1D0";
        s_VerticalHeader << "1E0";
        s_VerticalHeader << "1F0";

        s_VerticalHeader << "200";
        s_VerticalHeader << "210";
        s_VerticalHeader << "220";
        s_VerticalHeader << "230";
        s_VerticalHeader << "240";
        s_VerticalHeader << "250";
        s_VerticalHeader << "260";
        s_VerticalHeader << "270";
        s_VerticalHeader << "280";
        s_VerticalHeader << "290";
        s_VerticalHeader << "2A0";
        s_VerticalHeader << "2B0";
        s_VerticalHeader << "2C0";
        s_VerticalHeader << "2D0";
        s_VerticalHeader << "2E0";
        s_VerticalHeader << "2F0";

        s_VerticalHeader << "300";
        s_VerticalHeader << "310";
        s_VerticalHeader << "320";
        s_VerticalHeader << "330";
        s_VerticalHeader << "340";
        s_VerticalHeader << "350";
        s_VerticalHeader << "360";
        s_VerticalHeader << "370";
        s_VerticalHeader << "380";
        s_VerticalHeader << "390";
        s_VerticalHeader << "3A0";
        s_VerticalHeader << "3B0";
        s_VerticalHeader << "3C0";
        s_VerticalHeader << "3D0";
        s_VerticalHeader << "3E0";
        s_VerticalHeader << "3F0";
   }
   return s_VerticalHeader;
}

QSPDTableConfig::QSPDTableConfig()
{

}
