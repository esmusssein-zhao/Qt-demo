#ifndef STARTPUSHBUTTON_H
#define STARTPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QDebug>
#include <QPropertyAnimation>
class StartPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit StartPushButton(QWidget *parent = nullptr);
    StartPushButton(QString clickBeforPic,QString clickAfterPic="");//创建按钮的构造
    void zoom1();//按下
    void zoom2();//弹起
signals:
    void backClicked();
private:
    QString clickBeforPicIcon;
    QString clickAfterPicIcon;
public slots:
};

#endif // STARTPUSHBUTTON_H
