#include "qspdserver.h"
#include <icontroller.h>
#include <xcontrollerfactory.h>
#include <QEvent>
#include <QCoreApplication>
#include <qt_windows.h>
#include <qspdevent.h>
#include <qspdtableview.h>
#include <spdreadoption.h>
#include <qspdreadutil.h>
#include <asynclog.h>
#include <QDebug>

QSPDServer::QSPDServer(QThread * parent)
    :QThread(parent)
{
    c = IController::Create(new XControllerFactory());

    timer = new QTimer();
    connect(timer,&QTimer::timeout,this,[=](){
     static int iDuration = g_spdread_options->m_interval;
        emit sigTimerCount(iDuration);
        if(iDuration-- <=0)
        {
           iDuration = g_spdread_options->m_interval;
           clear();
           QMutexLocker lock(&m_Mutex);
           m_wc.notify_one();
        }
    });
    timer->start(1000);
}

QSPDServer::~QSPDServer()
{
    exit = true;
    m_wc.notify_one();
    wait();
}

void QSPDServer::addDevice(int s, void *device)
{
    QSPDTableView * d = static_cast<QSPDTableView *>(device);
    if(!d)return;
    d->setFileID(s);
    c->init(s,device);
    devices.push_back(d);
}

void QSPDServer::remove()
{
    for(int i = 0; i <devices.size(); i++)
    {
        devices[i]->removeFile();
    }
}

bool QSPDServer::event(QEvent *e)
{
    if(e->type() == static_cast<QEvent::Type>(QSPDEvent::ev_SPDRead))
    {
        QSPDEvent* ce = (QSPDEvent*)e;
        VMSpdData vmspdData  = ce->m_vmSpdData;
        int size = vmspdData.size();
        if(size >=1)c->Add(1,vmspdData[0]);
        if(size >=2)c->Add(2,vmspdData[1]);
        if(size >=3)c->Add(3,vmspdData[2]);
        if(size >=4)c->Add(4,vmspdData[3]);

        e->accept();
    }
    return QThread::event(e);
}

void QSPDServer::clear()
{
    for(int i = 0; i <devices.size(); i++)
    {
        devices[i]->clearSPDTable();
    }
}

void QSPDServer::run()
{
    while(!exit)
    {
        QMutexLocker lock(&m_Mutex);
        m_wc.wait(&m_Mutex);

        if(exit)return;

        VMSpdData vmspdData;
        vmspdData  = QSPDReadUtil::instance().read();
        QSPDEvent *ce = new QSPDEvent(vmspdData,QSPDEvent::ev_SPDRead);
        QCoreApplication::postEvent(this,ce);
    }
}
