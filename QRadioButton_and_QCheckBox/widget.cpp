#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(590,238);
    //创建性别qbuttonbox
    sexGroup = new QButtonGroup(this);
    //爸按钮添加进去，并设置id
    sexGroup->addButton(ui->man,1);
    sexGroup->addButton(ui->woman,2);
    //创建学历qbuttonbox
    levelGroup = new QButtonGroup(this);
    levelGroup->addButton(ui->lv1,3);
    levelGroup->addButton(ui->lv2,4);
    levelGroup->addButton(ui->lv3,5);
    levelGroup->addButton(ui->lv4,6);
    ui->frult_show->setPlaceholderText("选择你喜欢的水果来进行显示");
    ui->frult_show->setDisabled(true);
    ui->infoShow->setReadOnly(true);
    //单选框效果链接
    connect(ui->lv1,&QRadioButton::clicked,this,&Widget::radio_clicked);
    connect(ui->lv2,&QRadioButton::clicked,this,&Widget::radio_clicked);
    connect(ui->lv3,&QRadioButton::clicked,this,&Widget::radio_clicked);
    connect(ui->lv4,&QRadioButton::clicked,this,&Widget::radio_clicked);
    connect(ui->woman,&QRadioButton::clicked,this,&Widget::radio_clicked);
    connect(ui->man,&QRadioButton::clicked,this,&Widget::radio_clicked);
    //多选框点击效果链接
    connect(ui->apple,&QCheckBox::stateChanged,this,&Widget::check_box_clicked);
    connect(ui->banana,&QCheckBox::stateChanged,this,&Widget::check_box_clicked);
    connect(ui->pear,&QCheckBox::stateChanged,this,&Widget::check_box_clicked);
    connect(ui->strawberry,&QCheckBox::stateChanged,this,&Widget::check_box_clicked);
    connect(ui->watermelon,&QCheckBox::stateChanged,this,&Widget::check_box_clicked);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::radio_clicked()
{
    QString out;
    int flag1 = sexGroup->checkedId();
    //每个不同的id进行添加文本
    if(flag1==1)
        out+=ui->man->text();
    else if(flag1==2)
        out+=ui->woman->text();
    int flag2 = levelGroup->checkedId();
    if(flag2==3)
    {
        out+=ui->lv1->text();
        out+=QString("生");
    }
    else if(flag2==4)
    {
        out+=ui->lv2->text();
        out+=QString("生");
    }
    else if(flag2==5)
    {
        out+=ui->lv3->text();
        out+=QString("生");
    }
    else if(flag2==6)
        out+=ui->lv4->text();
    ui->infoShow->setText(out);
}


void Widget::on_all_chose_stateChanged(int arg1)
{
    //0为全部选，2为全选，1为半选
    if(arg1==0)
    {
        ui->apple->setCheckState(Qt::Unchecked);
        ui->banana->setCheckState(Qt::Unchecked);
        ui->pear->setCheckState(Qt::Unchecked);
        ui->strawberry->setCheckState(Qt::Unchecked);
        ui->watermelon->setCheckState(Qt::Unchecked);
    }
    else if(arg1==2)
    {
        ui->apple->setCheckState(Qt::Checked);
        ui->banana->setCheckState(Qt::Checked);
        ui->pear->setCheckState(Qt::Checked);
        ui->strawberry->setCheckState(Qt::Checked);
        ui->watermelon->setCheckState(Qt::Checked);
    }
}

void Widget::check_box_clicked()
{
    QString s=QString("爱吃：");
    //判断选择状态，2为选择，0为不选
    int apple_state = ui->apple->isChecked();
    int pear_state = ui->pear->isChecked();
    int strawberry_state = ui->strawberry->isChecked();
    int watermelon_state = ui->watermelon->isChecked();
    int banana_state = ui->banana->isChecked();
    if(apple_state && pear_state && strawberry_state && watermelon_state && banana_state)
        // 全部选中
        ui->all_chose->setCheckState(Qt::Checked);
    else if (!(apple_state || pear_state || strawberry_state || watermelon_state || banana_state))
        // 全部未选中
        ui->all_chose->setCheckState(Qt::Unchecked);
    else
        // 部分选中
        ui->all_chose->setCheckState(Qt::PartiallyChecked);
    //进行文字添加
    if(apple_state)
            s += ui->apple->text() += " ";
    if(pear_state)
        s += ui->pear->text() += " ";
    if(strawberry_state)
        s += ui->strawberry->text() += " ";
    if(watermelon_state)
        s += ui->watermelon->text() += " ";
    if(banana_state)
        s += ui->banana->text() += " ";
    ui->frult_show->setText(s);

}

