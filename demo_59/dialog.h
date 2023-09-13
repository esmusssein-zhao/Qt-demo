#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDebug>
#include <QDateTimeEdit>
#include <QMenu>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void change_underline(int);
    void change_italic(int);
    void change_bold(int);
    void on_black_clicked();

    void on_red_clicked();

    void on_blue_clicked();

    void on_plainTextEdit_customContextMenuRequested(const QPoint &pos);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
