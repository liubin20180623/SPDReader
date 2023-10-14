#ifndef ICONTROLLER_H
#define ICONTROLLER_H
#include <icontrollerfactory.h>
#include <qspddatatype.h>
#include <vector>
#include <map>

class XModel;
class IController
{
public:
    static IController* Create(IControllerFactory *f);
    virtual void init(int s,void* device);
    virtual void AddModel(int s=-1);
    virtual void Add(int s,MSpdData mspdData);

    IController();

    IView *v = 0;
    XModel *m = 0;
    IControllerFactory *f = 0;
    std::map<int,XModel*> tasks;
};

#endif // ICONTROLLER_H
