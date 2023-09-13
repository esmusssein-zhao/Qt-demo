#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QTime>
#include <QPixmap>
#include <QDebug>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_Left_clicked();

    void on_Center_clicked();

    void on_Right_clicked();

    void on_LineOn_clicked();

    void on_LineOff_clicked();

    void on_GetText_clicked();

    void on_ChangeText_clicked();

    void on_ChangePic_clicked();

private:
    Ui::Widget *ui;
    int index=0;
};

#endif // WIDGET_H
