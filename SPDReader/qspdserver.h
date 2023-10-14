#ifndef QSPDSERVER_H
#define QSPDSERVER_H

#include <QThread>
#include <QTimer>
#include <QMutex>
#include <QWaitCondition>

class QSPDTableView;
class IController;
class QSPDServer : public QThread
{
    Q_OBJECT
public:
    QSPDServer(QThread * parent = 0);
    ~QSPDServer();
    void addDevice(int s, void * device);
    void remove();

protected:
    virtual bool event(QEvent *e);
    virtual void run();
    void clear();

signals:
     void sigTimerCount(int count);

protected:
    QTimer* timer;
    IController *c = nullptr;
    QVector<QSPDTableView *> devices;
    QMutex m_Mutex;
    QWaitCondition m_wc;
    bool exit = false;
};

#endif // QSPDSERVER_H
