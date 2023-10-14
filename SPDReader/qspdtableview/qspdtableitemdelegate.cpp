#include "qspdtableitemdelegate.h"
#include <QPainter>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QPen>
#include <QDebug>

QSPDTableItemDelegate::QSPDTableItemDelegate(QObject *parent)
      : QStyledItemDelegate(parent)
{

}

QSPDTableItemDelegate::~QSPDTableItemDelegate()
{

}

void QSPDTableItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int row = index.row();
    int column = index.column();

    if(row == 0 || column == 0)
    {
       paintHeadData(painter,option,index);
    }
    else
    {
       paintText(painter,option,index);
    }
}

void QSPDTableItemDelegate::paintHeadData(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QString text = index.model()->data(index, Qt::DisplayRole).toString();

    QRect rect = option.rect;
    painter->fillRect(rect,QBrush(QColor(25,25,25)));

    QPen m_pen;
    m_pen.setColor(QColor(255,255,255));

    painter->setPen(m_pen);
    painter->setFont(QFont("Arial", 8, QFont::Normal));

    rect.setX(rect.x() + 2);
    painter->drawText(rect, Qt::AlignCenter, text);
}

void QSPDTableItemDelegate::paintText(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QString text = index.model()->data(index, Qt::DisplayRole).toString();
    QColor txtColor = index.model()->data(index, Qt::TextColorRole).toString();

    QRect rect = option.rect;
    painter->fillRect(rect,QBrush(QColor(25,25,25)));

    QPen m_pen;
    m_pen.setColor(txtColor);

    painter->setPen(m_pen);
    painter->setFont(QFont("Arial", 8, QFont::Normal));
    rect.setX(rect.x() + 2);
    painter->drawText(rect, Qt::AlignCenter, text);
}

