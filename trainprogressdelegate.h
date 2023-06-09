#ifndef TRAINPROGRESSDELEGATE_H
#define TRAINPROGRESSDELEGATE_H

#include <QPainter>
#include <QStyledItemDelegate>
#include <QEvent>
#include <QMouseEvent>
#include <QListView>
#include <QScroller>
#include <QDebug>
#pragma execution_character_set("utf-8")

class TrainProgressDelegate : public QStyledItemDelegate
{
public:
    TrainProgressDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;


    void setProgress(const int progress);

    int progress=2;

    int width_item=120;
    int height_item=80;
};

#endif // TRAINPROGRESSDELEGATE_H
