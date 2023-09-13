#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    label = new QLabel(this);
    label->setText("hello");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    //实例化画家对象，this为绘图设备
    QPainter painter(this);
    QPixmap pic;
    //使用qpixmap加载对应图片
    pic.load(":/res/pic.jpg");
    //使用画家在this设备上按照pic所加载的图片进行绘画（绘画起始位置x,y,绘画结束位置x,y,所绘对象）
    painter.drawPixmap(0,0,this->width(),this->height(),pic);

}
