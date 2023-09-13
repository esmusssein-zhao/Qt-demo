#include "backpushbutton.h"

BackPushButton::BackPushButton(QWidget *parent) : QPushButton(parent)
{

}
//创建按钮的重载构造
BackPushButton::BackPushButton(QString backBeforPic,QString backAfterPic)
{
    backBeforPicIcon=backBeforPic;
    backAfterPicIcon=backAfterPic;
    QPixmap pic;
    bool ret=pic.load(backBeforPic);
    if(!ret)
    {
        qDebug()<<"load error";
    }
    //设置按钮的大小
    this->setFixedSize(pic.width(),pic.height());
    //设置不规则形状，在这里按钮设置为圆形
//    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pic);
    //设置图标大小
    this->setIconSize(QSize(pic.width(),pic.height()));
}

void BackPushButton::backZoom1()
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
void BackPushButton::backZoom2()
{
    QPropertyAnimation* down=new QPropertyAnimation(this,"geometry");
    down->setDuration(200);
    down->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    down->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    down->setEasingCurve(QEasingCurve::OutBounce);
    down->start();
}
//重写按压效果
void BackPushButton::mousePressEvent(QMouseEvent *e)
{
    if(backBeforPicIcon!="")
    {
        QPixmap pic;
        bool ret = pic.load(backBeforPicIcon);
        if(!ret)
        {
            qDebug()<<"图片加载失败";
        }
        this->setFixedSize(pic.width(),pic.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pic);
        //设置图标大小
        this->setIconSize(QSize(pic.width(),pic.height()));
    }
    return QPushButton::mousePressEvent(e);
}
//重写释放效果
void BackPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(backAfterPicIcon!="")
    {
        QPixmap pic;
        bool ret = pic.load(backAfterPicIcon);
        if(!ret)
        {
            qDebug()<<"图片加载失败";
        }
        this->setFixedSize(pic.width(),pic.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pic);
        //设置图标大小
        this->setIconSize(QSize(pic.width(),pic.height()));
    }
    //其他内容交给mousePressEvent进行处理
    return QPushButton::mouseReleaseEvent(e);
}
