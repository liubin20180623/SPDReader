#include "qtableviewbasics.h"
#include <QHeaderView>
#include <QStandardItem>
#include <QStandardItemModel>

QTableViewBasics::QTableViewBasics(QWidget *parent)
     :QTableView(parent)
{
    dataModel = new QStandardItemModel(this);
    this->setModel(dataModel);

    selModel = new QItemSelectionModel(dataModel);
    this->setSelectionModel(selModel);
}

QTableViewBasics::~QTableViewBasics()
{

}

void QTableViewBasics::setHorizontalHeaderLabels(const QStringList &header)
{
    dataModel->setHorizontalHeaderLabels(header);
}

void QTableViewBasics::setVerticalHeaderLabels(const QStringList &header)
{
    dataModel->setVerticalHeaderLabels(header);
}

void QTableViewBasics::insertRow(int row)
{
     dataModel->insertRow(row);
}

void QTableViewBasics::removeRow(int row)
{
    dataModel->removeRow(row);
}

QVariant QTableViewBasics::getData(int row, int column)
{
    return dataModel->data(dataModel->index(row, column));
}

void QTableViewBasics::setData(int row, int column, QVariant value)
{
    dataModel->setData(dataModel->index(row,column),value);

}

void QTableViewBasics::setTextColor(int row, int column, QColor color)
{
    dataModel->setData(dataModel->index(row,column),color,Qt::TextColorRole);
}

void QTableViewBasics::setCellEnable(int row, int column, bool enable)
{
    dataModel->item(row,column)->setEditable(enable);
}

void QTableViewBasics::setCellForegroundColor(int row, int column, const QColor& color)
{
    dataModel->item(row,column)->setForeground(QBrush(color));
}

void QTableViewBasics::setCellBackgroundColor(int row, int column, const QColor& color)
{
    dataModel->item(row,column)->setBackground(QBrush(color));
}

bool QTableViewBasics::isCellSelected(int row, int column)
{
    return selModel->isSelected(dataModel->index(row,column));
}

void QTableViewBasics::resizeEvent(QResizeEvent *event)
{
    QTableView::resizeEvent(event);
}
