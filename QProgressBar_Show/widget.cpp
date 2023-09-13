#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->pro->setTextVisible(true);
    ui->pro->setMinimum(0);
    ui->pro->setMaximum(200);
    ui->pro->setFormat("%p%");
    t1 = new QTimer(this);
    t1->setInterval(50);
    connect(t1,&QTimer::timeout,this,&Widget::timerOut);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_start_clicked()
{
    t1->start();
}

void Widget::timerOut()
{
    if(ui->pro->value()<ui->pro->maximum())
    {
        ui->pro->setValue(ui->pro->value()+1);
        qDebug()<<ui->pro->value();
    }
    else
    {
        t1->stop();
        ui->label->setText("finish!");
    }
}
