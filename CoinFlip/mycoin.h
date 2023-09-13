#ifndef MYCOIN_H
#define MYCOIN_H

#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QDebug>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString coinPic);//初始状态的构造
    void mousePressEvent(QMouseEvent *e);
    void changeToF();//改变现在的状态
    bool changeFlag=false;
    QTimer* timer1;
    QTimer* timer2;
    int maxPic=8;
    int minPic=1;
    int x_axis;
    int y_axis;
    bool ToF;
    bool isWin=false;
private:
signals:

public slots:
};

#endif // MYCOIN_H
