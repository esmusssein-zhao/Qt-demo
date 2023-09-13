#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->number->setValue(1);
    ui->number->setMaximum(99);
    ui->number->setWrapping(true);
    ui->number->setAccelerated(true);
    ui->number->setSuffix("个");
    //使用占位符来进行初始内容的显示
    ui->info->setPlaceholderText("选择你的内容");
    //安宅添加顺序，index分别为0，1，2，3....
    ui->info->addItem("刀");
    ui->info->addItem("锤子");
    ui->info->addItem("老虎");
    ui->info->addItem("书");
    connect(ui->info,&QComboBox::currentIndexChanged,this,&Widget::changed_chose);
    connect(ui->info,&QComboBox::currentIndexChanged,this,&Widget::price_show);
    connect(ui->number,&QSpinBox::valueChanged,this,&Widget::price_show);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::changed_chose(int index)
{
    if(index==0)
        ui->price->setText("11");
    else if(index==1)
        ui->price->setText("22");
    else if(index==2)
        ui->price->setText("33000");
    else if(index==3)
        ui->price->setText("100");
}

void Widget::price_show()
{
    QString out;
    out="你买的"+ui->info->itemText(ui->info->currentIndex())+"共需"+QString::number(ui->price->text().toDouble() * ui->number->value())+"元";
    ui->information->setText(out);
}

