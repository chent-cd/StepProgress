#include "widget.h"
#include "ui_widget.h"
#include "trainprogressdelegate.h"

#include <QListView>
#include <QScrollArea>
#include <QStandardItemModel>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QListView *listView = ui->listView_trainProgress;
    listView->setSpacing(10);

    // �����Զ����QStyledItemDelegate��ΪitemDelegate����
    TrainProgressDelegate *delegate = new TrainProgressDelegate;
    listView->setItemDelegate(delegate);

    // �������ģ��
    QStringList items = {"Item 1", "Item 2", "Item 3", "Item 4", "Item 5", "Item 6", "Item 7", "Item 8", "Item 9", "Item 10"};
    QStandardItemModel *model = new QStandardItemModel;
    for (int i = 0; i < items.size(); i++) {
        QStandardItem *item = new QStandardItem(items.at(i));
        item->setData(i * 25, Qt::UserRole); // ���ý���ֵ
        model->appendRow(item);
    }
    listView->setModel(model);
    listView->setGridSize(QSize(260, 60));

}

Widget::~Widget()
{
    delete ui;
}


