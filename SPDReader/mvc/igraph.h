#ifndef IGRAPH_H
#define IGRAPH_H

class XModel;
class IGraph
{
public:
    virtual void init(void *d){
        this->device = d;
    }
    virtual void draw(XModel *m) = 0;
protected:
    void* device;
};

#endif // IGRAPH_H
