#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->R_s->setRange(0,255);
    ui->G_s->setRange(0,255);
    ui->B_s->setRange(0,255);
    ui->R_spin->setRange(0,255);
    ui->G_spin->setRange(0,255);
    ui->B_spin->setRange(0,255);
    this->setFixedSize(474,229);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_R_s_sliderMoved(int position)
{
    ui->R_spin->setValue(position);
    QString style = "background-color: rgb(" + QString::number(ui->R_s->value()) + "," + QString::number(ui->G_s->value())  + ","  + QString::number(ui->B_s->value()) + ");";
    ui->colour->setStyleSheet(style);
}


void Widget::on_G_s_sliderMoved(int position)
{
    ui->G_spin->setValue(position);
    QString style = "background-color: rgb(" + QString::number(ui->R_s->value()) + "," + QString::number(ui->G_s->value())  + ","  + QString::number(ui->B_s->value()) + ");";
    ui->colour->setStyleSheet(style);
}


void Widget::on_B_s_sliderMoved(int position)
{
    ui->B_spin->setValue(position);
    QString style = "background-color: rgb(" + QString::number(ui->R_s->value()) + "," + QString::number(ui->G_s->value())  + ","  + QString::number(ui->B_s->value()) + ");";
    ui->colour->setStyleSheet(style);
}


void Widget::on_R_spin_valueChanged(int arg1)
{
    ui->R_s->setValue(arg1);
    QString style = "background-color: rgb(" + QString::number(ui->R_s->value()) + "," + QString::number(ui->G_s->value())  + ","  + QString::number(ui->B_s->value()) + ");";
    ui->colour->setStyleSheet(style);
}


void Widget::on_G_spin_valueChanged(int arg1)
{
    ui->G_s->setValue(arg1);
    QString style = "background-color: rgb(" + QString::number(ui->R_s->value()) + "," + QString::number(ui->G_s->value())  + ","  + QString::number(ui->B_s->value()) + ");";
    ui->colour->setStyleSheet(style);
}


void Widget::on_B_spin_valueChanged(int arg1)
{
    ui->B_s->setValue(arg1);
    QString style = "background-color: rgb(" + QString::number(ui->R_s->value()) + "," + QString::number(ui->G_s->value())  + ","  + QString::number(ui->B_s->value()) + ");";
    ui->colour->setStyleSheet(style);
}

