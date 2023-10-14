#ifndef XSPDTABLEGRAPH_H
#define XSPDTABLEGRAPH_H

#include "igraph.h"
class XSPDTableGraph : public IGraph
{
public:
    virtual void draw(XModel *m);
};

#endif // XSPDTABLEGRAPH_H
