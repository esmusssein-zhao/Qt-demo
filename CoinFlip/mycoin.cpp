#include "mycoin.h"

MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
{

}

MyCoin::MyCoin(QString coinPic)
{
    timer1=new QTimer(this);
    timer2=new QTimer(this);
    QPixmap pic;
    bool ret=pic.load(coinPic);
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
    //触发翻转动画（正）
    connect(timer1,&QTimer::timeout,[=]()
    {
        QPixmap map;
        QString str=QString(":/res/Coin000%1").arg(minPic++);
        map.load(str);
        this->setFixedSize(map.width(),map.height());
        //设置不规则形状，在这里按钮设置为圆形
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(map);
        //设置图标大小
        this->setIconSize(QSize(map.width(),map.height()));
        //图片达到最终，定时器停止并重置minpic
        if(minPic>maxPic)
        {
            minPic=1;
            changeFlag=false;
            timer1->stop();
        }
    });
    //触发翻转动画（反）
    connect(timer2,&QTimer::timeout,[=]()
    {
        QPixmap map;
        QString str=QString(":/res/Coin000%1").arg(maxPic--);
        map.load(str);
        this->setFixedSize(map.width(),map.height());
        //设置不规则形状，在这里按钮设置为圆形
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(map);
        //设置图标大小
        this->setIconSize(QSize(map.width(),map.height()));
        //图片达到最终，定时器停止并重置maxpic
        if(minPic>maxPic)
        {
            maxPic=8;
            changeFlag=false;
            timer2->stop();
        }
    });

}

void MyCoin::changeToF()
{
    if(ToF)
    {
        timer1->start(30);
        changeFlag=true;
        ToF=false;
    }
    else
    {
        timer2->start(30);
        changeFlag=true;
        ToF=true;
    }
}

void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(changeFlag||isWin==true)
    {
        return;
    }
    else
        return QPushButton::mousePressEvent(e);
}
