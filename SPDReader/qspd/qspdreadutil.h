#ifndef QSPDREADUTIL_H
#define QSPDREADUTIL_H
#include <QObject>
#include <qspddatatype.h>
#include <qsmbus.h>

class QSPDReadUtil : public QObject
{
public:
    enum DDRType
    {
      DDR4 = 1,
      DDR5 = 2,
    };

   static QSPDReadUtil& instance();

   VMSpdData read();

protected:
   QSPDReadUtil(QObject *parent = 0)
       :QObject(parent){};

   int rowSize();
   int pageNO();
   int pageSize();
   BYTE convertOffset(BYTE offset);
   bool switchPage(BYTE slave_address,BYTE page);

private:
    QSmbus  m_smbus;
};

#endif // QSPDREADUTIL_H
