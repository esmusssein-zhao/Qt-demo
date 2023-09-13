#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include <QRadioButton>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QButtonGroup* sexGroup;
    QButtonGroup* levelGroup;
private slots:
    void radio_clicked();

    void on_all_chose_stateChanged(int arg1);

    void check_box_clicked();

};
#endif // WIDGET_H
