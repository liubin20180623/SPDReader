#ifndef IOBSERVER_H
#define IOBSERVER_H

class XSubject;
class IObserver
{
public:
    virtual void update(XSubject *sub) = 0;
};

#endif // IOBSERVER_H
