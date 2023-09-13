#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    time = new QTime();
    timer->setInterval(1000);
    ui->text->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    connect(ui->start,&QPushButton::clicked,this,&Widget::timerStart);
    connect(timer,&QTimer::timeout,this,&Widget::timerTimeOut);
    connect(timer,&QTimer::timeout,this,&Widget::textChange);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::timerStart()
{
    timer->start();
    *time = QTime::currentTime();
    ui->hour->display(time->hour());
    ui->minute->display(time->minute());
    ui->second->display(time->second());
    ui->timeGo->setText("");
}

void Widget::timerTimeOut()
{
    *time = time->addSecs(1);
    second++;
    ui->hour->display(time->hour());
    ui->minute->display(time->minute());
    ui->second->display(time->second());
}

void Widget::textChange()
{
    QString showMinute = QString::number(second/60);
    QString showSecond = QString::number(second%60);
    QString showInfo = showMinute+"分" + showSecond + "秒";
    ui->timeGo->setText(showInfo);
}

void Widget::on_reset_clicked()
{
    timer->stop();
}
