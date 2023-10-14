#ifndef QSPDDATATYPE_H
#define QSPDDATATYPE_H

#include <QObject>
#include <QMap>

typedef QMap<QString,QVector<std::tuple<QString,bool>>> MSpdData;
typedef QVector<MSpdData> VMSpdData;


#endif // QSPDDATATYPE_H
