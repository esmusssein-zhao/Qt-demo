#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_R_s_sliderMoved(int position);

    void on_G_s_sliderMoved(int position);

    void on_B_s_sliderMoved(int position);

    void on_R_s_2_valueChanged(int arg1);

    void on_G_spin_valueChanged(int arg1);

    void on_B_spin_valueChanged(int arg1);

    void on_R_spin_valueChanged(int arg1);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
