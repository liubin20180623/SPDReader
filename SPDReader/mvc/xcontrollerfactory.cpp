#include "xcontrollerfactory.h"
#include <xmodel.h>
#include <icontroller.h>
#include <xspdview.h>
#include <xspdtablegraph.h>

XControllerFactory::XControllerFactory()
{

}

IController *XControllerFactory::CreateC()
{
     return new IController();
}

XModel *XControllerFactory::CreateM()
{
    return new XModel();
}

IView *XControllerFactory::CreateV()
{
    XSPDView::get()->regView<XSPDTableGraph>(1);
    XSPDView::get()->regView<XSPDTableGraph>(2);
    XSPDView::get()->regView<XSPDTableGraph>(3);
    XSPDView::get()->regView<XSPDTableGraph>(4);

    return XSPDView::get();
}
