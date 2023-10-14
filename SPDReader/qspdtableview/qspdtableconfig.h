#ifndef QSPDTABLECONFIG_H
#define QSPDTABLECONFIG_H

#include <QObject>

class QSPDTableConfig
{
public:
    static QStringList getHorizontalHeader();
    static QStringList getVerticalHeader();

protected:
    QSPDTableConfig();

    static QStringList s_HorizontalHeader;
    static QStringList s_VerticalHeader;
};

#endif // QSPDTABLECONFIG_H
