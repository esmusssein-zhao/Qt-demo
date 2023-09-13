#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
//    ui->listWidget->setAlternatingRowColors(false);
    connect(ui->listWidget,&QListWidget::itemClicked,this,&Widget::clicked_once);
}


void Widget::on_radioButton_clicked()
{
    ui->listWidget->setViewMode(QListView::ListMode);
}


void Widget::on_radioButton_2_clicked()
{
    ui->listWidget->setViewMode(QListView::IconMode);
}

void Widget::clicked_once(QListWidgetItem *item)
{
    ui->lineEdit->setText(item->text());
    qDebug()<<item->text();
}

