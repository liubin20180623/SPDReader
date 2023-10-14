#ifndef XCONTROLLERFACTORY_H
#define XCONTROLLERFACTORY_H

#include <icontrollerfactory.h>
class XControllerFactory
        : public IControllerFactory
{
public:
     static XControllerFactory *get()
     {
         static XControllerFactory f;
         return &f;
     }

     virtual IController * CreateC();
     virtual XModel *CreateM();
     virtual IView *CreateV();

    XControllerFactory();
};

#endif // XCONTROLLERFACTORY_H
