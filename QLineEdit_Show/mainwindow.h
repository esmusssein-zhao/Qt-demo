#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_out_clicked();

    void on_normal_show_clicked();

    void on_password_show_clicked();

    void on_no_show_clicked();

    void on_lose_echo_show_clicked();

    void on_left_side_clicked();

    void on_center_side_clicked();

    void on_right_side_clicked();

    void on_out_control_clicked();

    void on_only_read_clicked();

    void on_read_and_write_clicked();

    void on_off_able_clicked();

    void on_on_able_clicked();

    void on_no_format_clicked();

    void on_key_clicked();

    void on_pushButton_20_clicked();

    void on_tc_1_textChanged(const QString &arg1);

    void on_tc_2_textChanged(const QString &arg1);

    void on_ef_1_editingFinished();

    void on_ef_2_editingFinished();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
