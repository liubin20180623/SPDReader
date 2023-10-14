#ifndef QTOOL_H
#define QTOOL_H

class QTool
{
public:
    static QTool instance(){
        static QTool m;
        return m;
    }

   void CreateStartupMenuLink(bool IsAutoRun);

protected:
   QTool(){};
};

#endif // QTOOL_H
