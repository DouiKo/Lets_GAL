#ifndef ITEMDELEGATE_H
#define ITEMDELEGATE_H

#include <QStyledItemDelegate>
#include "gameitem.h"

class ItemDelegate : public QStyledItemDelegate
{
public:
    ItemDelegate();

    ~ItemDelegate();

    //    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    //    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    //    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // ITEMDELEGATE_H
