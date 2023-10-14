#ifndef XSUBJECT_H
#define XSUBJECT_H
#include <vector>

class IObserver;
class XSubject
{
public:
    XSubject();
    int type = 0;

    //通知观察者,即显示的device对象
    virtual void notify();

    //添加观察者
    void attach(IObserver *ob);

protected:
   std::vector<IObserver *> obs;
};

#endif // XSUBJECT_H
