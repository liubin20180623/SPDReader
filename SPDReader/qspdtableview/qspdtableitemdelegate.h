#ifndef QSPDTABLEITEMDELEGATE_H
#define QSPDTABLEITEMDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class QSPDTableItemDelegate : public QStyledItemDelegate
{
public:
   explicit QSPDTableItemDelegate(QObject *parent = nullptr);
   ~QSPDTableItemDelegate();

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    void paintHeadData(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paintText(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // QSPDTABLEITEMDELEGATE_H
