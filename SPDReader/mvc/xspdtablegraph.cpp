#include "xspdtablegraph.h"
#include <qspdtableview.h>
#include <xmodel.h>

void XSPDTableGraph::draw(XModel *m)
{
   QSPDTableView* p = static_cast< QSPDTableView*>(device);
   if(!p)return;

   p->updateSPDTable(m->mspdData);
}

