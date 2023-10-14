#include "xspdview.h"
#include <xmodel.h>
#include <QWidget>
#include <QPainter>
#include <QDebug>

void XSPDView::update(XSubject *sub)
{
    if(!sub) return;
    XModel *m = static_cast<XModel *>(sub);
    views[m->type]->draw(m);
}

void XSPDView::initDevice(int s,void *d)
{
    if(views.count(s)){
        views[s]->init(d);
    }
}

XSPDView::XSPDView()
{

}
