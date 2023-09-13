#ifndef CENTERFACE_H
#define CENTERFACE_H

#include <QWidget>
#include <QPushButton>
#include <QPixmap>
#include <QDebug>

class CenterFace : public QPushButton
{
    Q_OBJECT
public:
    explicit CenterFace(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void changeWinFlag(int i);//是否胜利或
private:
    int winFlag = 2;//1为胜利，0为失败，其他为正常状态
signals:

public slots:
};

#endif // CENTERFACE_H
