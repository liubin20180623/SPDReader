#include "icontroller.h"
#include <iview.h>
#include <xmodel.h>
#include <QDebug>

IController *IController::Create(IControllerFactory *f)
{
    if(!f)return nullptr;
    IController *c = f->CreateC();
    c->f = f;
    c->m = f->CreateM();
    c->v = f->CreateV();
    return c;
}

void IController::init(int s,void *device)
{
    AddModel(s);
    v->initDevice(s,device);
}

void IController::AddModel(int s)
{
    //创建模型,添加观察者
    m = f->CreateM();
    m->attach(v);
    m->type = s;
    tasks[s] = m;
}

void IController::Add(int s,MSpdData mspdData)
{
    if(!tasks.count(s))return;
    tasks[s]->Add(mspdData);
    tasks[s]->notify();
}

IController::IController()
{

}
