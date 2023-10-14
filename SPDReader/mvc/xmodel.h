#ifndef XMODEL_H
#define XMODEL_H

#include <xsubject.h>
#include <qspddatatype.h>

class XModel : public XSubject
{
public:
    MSpdData mspdData;
    void Add(MSpdData mspdData);
};

#endif // XMODEL_H
