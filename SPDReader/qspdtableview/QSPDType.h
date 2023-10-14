#ifndef QSPDTYPE_H
#define QSPDTYPE_H

#include <QObject>

typedef QMap<QString,QVector<std::tuple<QString,bool>>> MSpdData;
typedef QVector<MSpdData> VMSpdData;


#endif // QSPDTYPE_H
