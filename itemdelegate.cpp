#include "itemdelegate.h"

#include <QPainter>
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>

ItemDelegate::ItemDelegate()
{
}

ItemDelegate::~ItemDelegate()
{
}

//QWidget *ItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{

//}

//void ItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
//{

//}

//void ItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
//{

//}

void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.isValid())
    {
//        painter->save();
//        qDebug()<<option.rect;
        painter->setRenderHint(QPainter::Antialiasing);

        QVariant variant = index.data(Qt::UserRole + 1);
        GameItem gameData = variant.value<GameItem>();

        QRectF rect;
        rect.setX(option.rect.x() + 5);
        rect.setY(option.rect.y());
        rect.setWidth(option.widget->width() - 15);
        rect.setHeight(option.rect.height());

        //绘制每个item下边框
        QPen pen(QColor(235,235,235));
        pen.setWidthF(0.5);
        painter->setPen(pen);
        painter->drawLine(rect.left(),rect.bottom(),rect.right(),rect.bottom());

        //响应鼠标状态
        if(option.state.testFlag(QStyle::State_Selected)){
            painter->setPen(QColor(236,239,255));
            painter->setBrush(QColor(236,239,255));
            painter->drawRoundedRect(rect,2,2);

        }else if(option.state.testFlag(QStyle::State_MouseOver)){
            painter->setPen(QColor(235,235,235));
            painter->setBrush(QColor(235,235,235));
            painter->drawRoundedRect(rect,2,2);

            painter->setPen(Qt::gray);
            painter->setBrush(Qt::gray);
            painter->drawRoundedRect(rect.left() + 390,rect.top() + 9,18,18,5,5);
        }

        //绘制数据位置
        painter->setPen(QColor(68,68,68));
        painter->setFont(QFont("等线", 8));
        QRect imageRect = QRect(rect.left() +15,  rect.top() + 10, 16, 16);
        QRect nameRect = QRect(rect.left()  +35,  rect.top() + (rect.height() - painter->fontMetrics().height()) / 2, 400, painter->fontMetrics().height());
        QRect tagsRect = QRect(rect.left()  +445, rect.top() + (rect.height() - painter->fontMetrics().height()) / 2, 200, painter->fontMetrics().height());
        QRect timeRect = QRect(rect.right() -70,  rect.top() + (rect.height() - painter->fontMetrics().height()) / 2, 70,  painter->fontMetrics().height());

        painter->setPen(QColor(68,68,68));
        painter->setFont(QFont("等线", 8));
        painter->drawText(nameRect,Qt::AlignLeft,gameData.getName());
//        painter->drawRect(nameRect);
        painter->drawText(tagsRect,Qt::AlignLeft,gameData.getTagsString());
//        painter->drawRect(tagsRect);
        painter->drawText(timeRect,Qt::AlignLeft,gameData.getTime());
//        painter->drawRect(timeRect);
        //可能需要使用线程优化性能
        painter->drawPixmap(imageRect,gameData.getIcon());

//        painter->restore();
    }
}

QSize ItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(option.rect.width(), 36);
}

