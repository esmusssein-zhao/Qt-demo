#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Echo_mode_edit->setPlaceholderText(QString("文本输入显示方式"));
    ui->alignment_edit->setPlaceholderText(QString("文字对齐方式显示"));
    ui->control_show->setPlaceholderText(QString("文字读写控制"));
    ui->format_show->setPlaceholderText(QString("文字格式控制"));
    ui->tc_3->setReadOnly(true);
    ui->ef_3->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_out_clicked()
{
    QMessageBox::information(this,"内容",ui->Echo_mode_edit->text());
}


void MainWindow::on_normal_show_clicked()
{
    ui->Echo_mode_edit->setEchoMode(QLineEdit::Normal);
}


void MainWindow::on_password_show_clicked()
{
    ui->Echo_mode_edit->setEchoMode(QLineEdit::Password);
}


void MainWindow::on_no_show_clicked()
{
    ui->Echo_mode_edit->setEchoMode(QLineEdit::NoEcho);
}


void MainWindow::on_lose_echo_show_clicked()
{
    ui->Echo_mode_edit->setEchoMode(QLineEdit::PasswordEchoOnEdit);
}


void MainWindow::on_left_side_clicked()
{
    ui->alignment_edit->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
}


void MainWindow::on_center_side_clicked()
{
    ui->alignment_edit->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
}


void MainWindow::on_right_side_clicked()
{
    ui->alignment_edit->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
}


void MainWindow::on_out_control_clicked()
{
    QMessageBox::information(this,"内容",ui->control_show->text());
}


void MainWindow::on_only_read_clicked()
{
    ui->control_show->setReadOnly(true);
}


void MainWindow::on_read_and_write_clicked()
{
    ui->control_show->setReadOnly(false);
}


void MainWindow::on_off_able_clicked()
{
    ui->control_show->setDisabled(true);
}


void MainWindow::on_on_able_clicked()
{
    ui->control_show->setDisabled(false);
}


void MainWindow::on_no_format_clicked()
{
    ui->format_show->setInputMask("");
}


void MainWindow::on_key_clicked()
{
    ui->format_show->setInputMask("999-9999-9999;c");
}


void MainWindow::on_pushButton_20_clicked()
{
    ui->format_show->setInputMask(">AAAAA-AAAAA-AAAAA-AAAAA-AAAAA;#");
}


void MainWindow::on_tc_1_textChanged(const QString &arg1)
{
        ui->tc_3->setText(QString::number(arg1.toInt() - ui->tc_2->text().toInt()));
}


void MainWindow::on_tc_2_textChanged(const QString &arg1)
{
    ui->tc_3->setText(QString::number(ui->tc_1->text().toInt()-arg1.toInt()));
}


void MainWindow::on_ef_1_editingFinished()
{
    ui->ef_3->setText(QString::number(ui->ef_1->text().toInt() + ui->ef_2->text().toInt()));
}


void MainWindow::on_ef_2_editingFinished()
{
    ui->ef_3->setText(QString::number(ui->ef_1->text().toInt() + ui->ef_2->text().toInt()));
}

