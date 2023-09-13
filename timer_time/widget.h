#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QTime>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QTimer* timer;
    QTime* time;
    int second = 0;
private slots:
    void timerStart();
    void timerTimeOut();
    void textChange();
    void on_reset_clicked();
};

#endif // WIDGET_H
