#ifndef XSPDVIEW_H
#define XSPDVIEW_H
#include <iview.h>
#include <igraph.h>
#include <map>

class IGraph;
class XSPDView : public IView
{
public:
    static XSPDView * get()
    {
        static XSPDView m;
        return &m;
    }

    virtual void update(XSubject *sub);

    //显示目标
    virtual void initDevice(int s,void * d);

    //注册类
    template<class ViewClass>
    IGraph *regView(int type)
    {
        ViewClass *view = new ViewClass();
        views.insert(std::make_pair(type,view));
        return view;
    }

protected:
    std::map<int,IGraph*>views;
    XSPDView();
};

#endif // XSPDVIEW_H
