#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->infoShow->setReadOnly(true);
    connect(ui->name,&QLineEdit::textChanged,this,&MainWindow::info_change);
    connect(ui->sex,&QComboBox::currentIndexChanged,this,&MainWindow::info_change);
    connect(ui->grade,&QComboBox::currentTextChanged,this,&MainWindow::info_change);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::info_change()
{
    QString out;
    out = ui->name->text() +ui->sex->currentText()+ui->grade->currentText();
    ui->infoShow->setText(out);

}

