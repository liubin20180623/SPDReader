#ifndef QIOPORT_H
#define QIOPORT_H
#include <QObject>
#include <qwinring0Driver.h>

class QIOPort
{
public:
    QIOPort();
    QIOPort(WORD address);
    ~QIOPort();

    template<class T>
    T read(WORD port);

    template<class T>
    void write(WORD port, T value);

private:
    WORD baseAddress;
};

template<class T>
T QIOPort::read(WORD offset)
{
    T data = 0;
    if(typeid(T) == typeid(BYTE))
    {
      data = QWinRing0Driver::instance().readIoPortByte(baseAddress+offset);
    }
    else if(typeid(T) == typeid(WORD))
    {
      data = QWinRing0Driver::instance().readIoPortWord(baseAddress+offset);
    }
    else if(typeid(T) == typeid(DWORD))
    {
      data = QWinRing0Driver::instance().readIoPortDWord(baseAddress+offset);
    }

    return data;
}

template<class T>
void QIOPort::write(WORD offset, T value)
{
    if(typeid(T) == typeid(BYTE))
    {
       QWinRing0Driver::instance().writeIoPortByte(baseAddress+offset,value);
    }
    else if(typeid(T) == typeid(WORD))
    {
       QWinRing0Driver::instance().writeIoPortWord(baseAddress+offset,value);
    }
    else if(typeid(T) == typeid(DWORD))
    {
       QWinRing0Driver::instance().writeIoPortDWord(baseAddress+offset,value);
    }
}

#endif // QIOPORT_H
