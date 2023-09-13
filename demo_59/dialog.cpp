#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->underline,&QCheckBox::stateChanged,this,&Dialog::change_underline);
    connect(ui->italic,&QCheckBox::stateChanged,this,&Dialog::change_italic);
    connect(ui->bold,&QCheckBox::stateChanged,this,&Dialog::change_bold);
    ui->black->setChecked(true);
//    QSet<int>a;
//    a.insert(3);
//    a.insert(1);
//    a.insert(5);
//    for (auto& b : a)
//        qDebug() << b << endl;
//    QMap<QString,int>a;
//    a.insert("hello",1);
//    QDateTimeEdit* date = new QDateTimeEdit(this);
    ui->dateTime->setDateTime(QDateTime::currentDateTime());

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::change_underline(int args)
{
    if(args==2)
    {
        QFont underline = ui->text->font();
        underline.setUnderline(true);
        ui->text->setFont(underline);
    }
    else if(args==0)
    {
        QFont underline = ui->text->font();
        underline.setUnderline(false);
        ui->text->setFont(underline);
    }
}

void Dialog::change_italic(int args)
{
    if(args==2)
    {
        QFont italic = ui->text->font();
        italic.setItalic(true);
        ui->text->setFont(italic);
    }
    else if(args==0)
    {
        QFont italic = ui->text->font();
        italic.setItalic(false);
        ui->text->setFont(italic);
//        ui->text->setFontItalic(false);
    }
}

void Dialog::change_bold(int args)
{
    if(args==2)
    {
        QFont bold = ui->text->font();
        bold.setBold(true);
        ui->text->setFont(bold);
//        ui->text->setFont(ui->text->font().setBold(true));

    }
    else if(args==0)
    {
        QFont bold = ui->text->font();
        bold.setBold(false);
        ui->text->setFont(bold);
//        ui->text->setFont(ui->text->font().setBold(false));
    }
}

void Dialog::on_black_clicked()
{
    ui->text->setTextColor(QColor(0,0,0));
}

void Dialog::on_red_clicked()
{
    ui->text->setTextColor(QColor(255,0,0));
}

void Dialog::on_blue_clicked()
{
    ui->text->setTextColor(QColor(0,0,255));
}

void Dialog::on_plainTextEdit_customContextMenuRequested(const QPoint &pos)
{
    QMenu* menu = ui->plainTextEdit->createStandardContextMenu();
    menu->exec(pos);
}
