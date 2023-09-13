#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_Left_clicked()
{
    ui->Alignment->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
}

void Widget::on_Center_clicked()
{
    ui->Alignment->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
}

void Widget::on_Right_clicked()
{
    ui->Alignment->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
}

void Widget::on_LineOn_clicked()
{
    ui->ChangeLine->setWordWrap(true);
    this->resize(300,500);
}

void Widget::on_LineOff_clicked()
{
    ui->ChangeLine->setWordWrap(false);
}

void Widget::on_GetText_clicked()
{
    QMessageBox box;
    box.setWindowTitle("文本内容");
    box.setText(ui->TextShow->text());
    box.setButtonText(QMessageBox::Ok,QString("确认"));
    box.exec();
}

void Widget::on_ChangeText_clicked()
{
    ui->TextShow->setText(QTime::currentTime().toString("h:m:s ap"));
}

void Widget::on_ChangePic_clicked()
{
    QPixmap px;

    // 将图标文件加载到 QPixmap
    if(index == 0) {
        px.load(QString(":/res/strawberry.ico"));
        index++;
    } else
    {
        px.load(QString(":/res/apple.ico"));
        index = 0;
    }
    // 把图片设置到标签上
    ui->picload->setPixmap(px);
    // 不要缩放，否则拉伸导致失真
    ui->picload->setScaledContents(false);
    // 图片在标签中居中显示（水平和垂直方向均居中）
    ui->picload->setAlignment(Qt::AlignCenter);
    }

