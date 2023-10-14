#ifndef IVIEW_H
#define IVIEW_H
#include <iobserver.h>

class IView : public IObserver
{
public:
    //显示目标
    virtual void initDevice(int s, void * d) = 0;

};

#endif // IVIEW_H
