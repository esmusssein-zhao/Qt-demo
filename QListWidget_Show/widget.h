#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QDebug>
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
    void on_radioButton_clicked();

    void on_radioButton_2_clicked();
    void clicked_once(QListWidgetItem *item);
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
