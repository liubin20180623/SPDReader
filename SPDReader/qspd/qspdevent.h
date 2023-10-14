#ifndef QSPDEVENT_H
#define QSPDEVENT_H
#include <QEvent>
#include <qspddatatype.h>

class QSPDEvent: public QEvent
{
public:
    enum Type
    {
        ev_SPDRead = QEvent::User + 1,
    };
    Q_ENUM(Type);
    QSPDEvent(VMSpdData vmSpdData,Type type):QEvent(QEvent::Type(type))
    {
      m_vmSpdData = vmSpdData;
    }

public:
    VMSpdData m_vmSpdData;
};

#endif // QSPDEVENT_H
