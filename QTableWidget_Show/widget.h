#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QStringList>
#include <QHeaderView>
#include <QTableWidgetItem>

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
    void on_color_change_stateChanged(int arg1);

    void on_choose_everyone_clicked();

    void on_choose_line_clicked();

    void on_change_everyone_stateChanged(int arg1);

    void on_show_line_stateChanged(int arg1);

    void on_show_row_stateChanged(int arg1);

    void infrShow(int row);

    void addTableItem();

    void changeTableItem();
    void on_insert_clicked();

    void on_del_clicked();

private:
    Ui::Widget *ui;
    void appendOneRow(QString name,QString sex,int age,QString address);
};
#endif // WIDGET_H
