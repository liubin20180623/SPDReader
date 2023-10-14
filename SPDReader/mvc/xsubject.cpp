#include "xsubject.h"
#include <iobserver.h>

XSubject::XSubject()
{

}

void XSubject::notify()
{
    for(int i = 0; i < obs.size(); i++)
    {
        obs[i]->update(this);
    }
}

void XSubject::attach(IObserver *ob)
{
    this->obs.push_back(ob);
}
