#ifndef QTABLEVIEWBASICS_H
#define QTABLEVIEWBASICS_H

#include <QTableView>

class QStandardItemModel;
class QItemSelectionModel;
class QTableViewBasics : public QTableView
{
  Q_OBJECT
public:
    QTableViewBasics(QWidget *parent = nullptr);
    virtual ~QTableViewBasics();

    void setHorizontalHeaderLabels(const QStringList& header);
    void setVerticalHeaderLabels(const QStringList& header);

    void insertRow(int row);
    void removeRow(int row);

    QVariant getData(int row, int column);
    void setData(int row, int column,QVariant value);

    void setTextColor(int row,int column,QColor color);

    void setCellEnable(int row, int column,bool enable);
    void setCellForegroundColor(int row, int column,const QColor& color);
    void setCellBackgroundColor(int row, int column,const QColor& color);

    bool isCellSelected(int row, int column);

protected:
    virtual void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
    QStandardItemModel* dataModel   = nullptr;
    QItemSelectionModel* selModel = nullptr;
};

#endif // QTABLEVIEWBASICS_H
