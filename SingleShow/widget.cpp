#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //qt4
    connect(ui->change_size,SIGNAL(clicked(bool)),this,SLOT(change_size()));
    //qt5+
    connect(ui->max_size,&QPushButton::clicked,this,&Widget::max);
    //c++11
    connect(ui->original,&QPushButton::clicked,this,[=](){
        this->showNormal();
    //设计师界面转到槽
    //UI设计师界面-信号槽编辑器
    });
}

Widget::~Widget()
{
    delete ui;
}
void Widget::max()
{
    this->showMaximized();
}

void Widget::on_min_size_clicked()
{
    this->showMinimized();
}

void Widget::change_size()
{
    this->resize(600,600);
}
