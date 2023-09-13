#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QMenuBar>
#include <QDebug>
#include <QMessageBox>
#include <QPainter>
#include "backpushbutton.h"
#include <QTimer>
#include <QLabel>
#include "mycoin.h"
#include "dataconfig.h"

//不能在此处添加头文件
//#include "playscene.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int index);//关卡选择，index为传入管卡数
private:
    int levalIndex;
    void paintEvent(QPaintEvent *);//重写绘画事件
     BackPushButton* back=nullptr;//返回按钮
     int gameInfo[4][4];//保存游戏状态
     MyCoin* coinButton[4][4];//硬币按钮按键
     bool win=false;//胜利条件
signals:
    void backClicked2();//被点击的信号
public slots:
};

#endif // PLAYSCENE_H
