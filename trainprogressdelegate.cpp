#include "trainprogressdelegate.h"

TrainProgressDelegate::TrainProgressDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

void TrainProgressDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);

    qDebug()<<index.row();

    // 绘制圆角矩形
    QRect rect = option.rect.adjusted(2, 2, -2, -2);
    // 设置抗锯齿渲染
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::NoPen);
    if(index.row()<progress)
    {
        painter->setBrush(QColor(0 , 255, 0));
    }
    else
    {
        painter->setBrush(QColor(255 , 0, 0));
    }
    painter->drawRoundedRect(rect, 10, 10);

    // 绘制文字
    QString text = index.data(Qt::DisplayRole).toString();
    painter->setPen(Qt::white);
    painter->drawText(rect, Qt::AlignCenter, text);


    // 绘制箭头
    if (index.row() < index.model()->rowCount() - 1) {
        QListView *listView = const_cast<QListView*>(qobject_cast<const QListView*>(option.widget));
        int midLine = (listView->gridSize().width()-rect.width())/2;

        QRect arrowRect = option.rect.adjusted(rect.width() , 0, listView->gridSize().width(), 0);
        QPainterPath path;
        path.moveTo(arrowRect.x()+midLine-40,arrowRect.top()+30);
        path.lineTo(arrowRect.x()+midLine-10,arrowRect.center().y());
        path.lineTo(arrowRect.x()+midLine-40,arrowRect.bottom()-30);

        path.lineTo(arrowRect.x()+midLine-20,arrowRect.bottom()-30);
        path.lineTo(arrowRect.x()+midLine+10,arrowRect.center().y());
        path.lineTo(arrowRect.x()+midLine-20,arrowRect.top()+30);

        path.moveTo(arrowRect.x()+midLine,arrowRect.top()+30);
        path.lineTo(arrowRect.x()+midLine+30,arrowRect.center().y());
        path.lineTo(arrowRect.x()+midLine,arrowRect.bottom()-30);

        path.lineTo(arrowRect.x()+midLine+20,arrowRect.bottom()-30);
        path.lineTo(arrowRect.x()+midLine+50,arrowRect.center().y());
        path.lineTo(arrowRect.x()+midLine+20,arrowRect.top()+30);
        painter->setBrush(Qt::blue);
        painter->setPen(QPen(Qt::white, 2));
        painter->drawPath(path);
    }


}

bool TrainProgressDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    // 处理鼠标事件
    if (event->type() == QEvent::MouseMove)
    {
        QListView *listView = const_cast<QListView*>(qobject_cast<const QListView*>(option.widget));
        if (listView) {
            listView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
            QScroller *scroller = QScroller::scroller(listView->viewport());
            scroller->grabGesture(listView->viewport(), QScroller::LeftMouseButtonGesture);
            QScrollerProperties properties = scroller->scrollerProperties();
            properties.setScrollMetric(QScrollerProperties::DragVelocitySmoothingFactor, 0.3);
            properties.setScrollMetric(QScrollerProperties::FrameRate, QScrollerProperties::Fps60);
            scroller->setScrollerProperties(properties);

//            // 连接滚动结束信号
//            QObject::connect(scroller, &QScroller::stateChanged, listView, [listView,this](QScroller::State state){
//                if (state == QScroller::Inactive) {
//                    for(int i=0;i<10;i++)
//                    {
//                        QModelIndex index = listView->indexAt(QPoint((width_item/2)+i*5, (listView->height()/2)));
//                        if (index.isValid()) {
//                            listView->scrollTo(index, QAbstractItemView::PositionAtTop);
//                            break;
//                        }
//                    }
//                }
//            });
        }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

QSize TrainProgressDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(width_item, height_item);
}

void TrainProgressDelegate::setProgress(const int progress)
{
    this->progress=progress;

}
