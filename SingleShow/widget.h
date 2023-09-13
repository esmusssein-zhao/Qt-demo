#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

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
    void on_min_size_clicked();
    void change_size();
private:
    Ui::Widget *ui;
    void max();

};

#endif // WIDGET_H
