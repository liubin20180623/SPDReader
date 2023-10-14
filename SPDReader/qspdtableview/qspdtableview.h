#ifndef QSPDTABLEVIEW_H
#define QSPDTABLEVIEW_H

#include <qtableviewbasics.h>
#include <qspddatatype.h>

class QSPDTableItemDelegate;
class QSPDTableView : public QTableViewBasics
{
    Q_OBJECT
public:
    QSPDTableView(QWidget *parent = nullptr);
    ~QSPDTableView();

    void InitTable(int rowHeight = 20,
                   bool Editable=false,
                   bool isSorting = false,
                   bool verticalHeadVisible=false,
                   bool horizontalHeadVisible=false,
                   bool isLastTensile = false,
                   bool isShowGrid = false);

     void setFileID(int id);
     void removeFile();
     void clearSPDTable();
     void updateSPDTable(MSpdData& mspdData);

private:
    void initSPDTable();
    void saveSPDTable(MSpdData &mspdData);
    void readSPDTable(MSpdData &mspdData);

private:
    QSPDTableItemDelegate *delegate = nullptr;
    int m_id;
    QString s_filePath;
    static QMap<QString,QColor> m_TxtColors;
};

#endif // QSPDTABLEVIEW_H
