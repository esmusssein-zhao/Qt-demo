#ifndef CHOOSELEVEL_H
#define CHOOSELEVEL_H

#include <QMainWindow>
#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include "backpushbutton.h"
#include "startpushbutton.h"
#include <QMessageBox>
#include <QLabel>
#include "playscene.h"
class ChooseLevel : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevel(QWidget *parent = nullptr);
signals:
    void backClicked1();//被点击的信号
    void backClicked2();
private:
    PlayScene* pSence=nullptr;//游戏
    StartPushButton* back=nullptr;//按钮
    void paintEvent(QPaintEvent *);//重写绘画事件
public slots:
};

#endif // CHOOSELEVEL_H
