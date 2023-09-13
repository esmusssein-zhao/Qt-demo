#ifndef BACKPUSHBUTTON_H
#define BACKPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include <QPropertyAnimation>
#include <QPixmap>

class BackPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit BackPushButton(QWidget *parent = nullptr);
    BackPushButton(QString backBeforPic,QString backAfterPic);//创建按钮的构造
    void backZoom1();//按下
    void backZoom2();//弹起
    void mousePressEvent(QMouseEvent *e);//重写按压效果
    void mouseReleaseEvent(QMouseEvent *e);//重写释放效果
private:
    QString backBeforPicIcon;//按压前图片位置
    QString backAfterPicIcon;//按压后图片位置
signals:
public slots:
};

#endif // BACKPUSHBUTTON_H
