#ifndef ICONTROLLERFACTORY_H
#define ICONTROLLERFACTORY_H

class IController;
class XModel;
class IView;
class IControllerFactory
{
public:
    virtual IController *CreateC() = 0;
    virtual XModel *CreateM() = 0;
    virtual IView *CreateV() = 0;
};

#endif // ICONTROLLERFACTORY_H
