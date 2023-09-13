#include "startpushbutton.h"

StartPushButton::StartPushButton(QWidget *parent) : QPushButton(parent)
{

}

//创建按钮的构造
StartPushButton::StartPushButton(QString clickBeforPic,QString clickAfterPic)
{
    clickBeforPicIcon=clickBeforPic;
    clickAfterPicIcon=clickAfterPic;
    QPixmap pic;
    bool ret=pic.load(clickBeforPic);
    if(!ret)
    {
        qDebug()<<"load error";
    }
    //设置按钮的大小
    this->setFixedSize(pic.width(),pic.height());
    //设置不规则形状，在这里按钮设置为圆形
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pic);
    //设置图标大小
    this->setIconSize(QSize(pic.width(),pic.height()));
}
//按下
void StartPushButton::zoom1()
{
    //创建动画效果类
    QPropertyAnimation* up=new QPropertyAnimation(this,"geometry");
    //设置持续时间
    up->setDuration(200);
    //设置起始位置
    up->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    up->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //运动轨迹
    up->setEasingCurve(QEasingCurve::OutBounce);
    up->start();
}
//弹起
void StartPushButton::zoom2()
{
    QPropertyAnimation* down=new QPropertyAnimation(this,"geometry");
    down->setDuration(200);
    down->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    down->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    down->setEasingCurve(QEasingCurve::OutBounce);
    down->start();
}
