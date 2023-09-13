#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置行数
//    ui->table->setRowCount(4);
    //设置列，默认显示列数
    ui->table->setColumnCount(4);
    //存放行头内容，使用一个qstringlist
    QStringList rowInfo;
    rowInfo << "姓名";
    rowInfo <<"性别";
    rowInfo <<"年龄";
    rowInfo <<"籍贯";
    //设置行内容
    ui->table->setHorizontalHeaderLabels(rowInfo);
    //设置列表头 - 通常不设置，则默认为行号
//    table->setVerticalHeaderLabels();
    //先自适应宽度，按照tablewidget宽度进行自动调整
    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //对头部对应位置进行调整
//    ui->table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    //将给定列的宽度设置为宽度
//    ui->table->setColumnWidth(0, 80);
    //setitem第三个参数必须是一个QTableWidgetItem的指针，前两个参数从0开始
//    QTableWidgetItem*  firt=new QTableWidgetItem("hello");
//    ui->table ->setItem(1,1,firt);
    //设置单元格格式
//    firt->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    //自己编写每行的添加函数
    appendOneRow("李雷", "男", 12, "广东");
    appendOneRow("韩梅梅", "女", 11, "北京");
    appendOneRow("林涛", "男", 13, "上海");
    appendOneRow("雷李", "男", 17, "贵州");
    appendOneRow("德梅", "女", 15, "云南");
    appendOneRow("涛林", "男", 13, "陕西");
    //设置相关属性的默认情况
    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->choose_everyone->setChecked(true);
    ui->show_line->setChecked(true);
    ui->show_row->setChecked(true);
    //cellcllcked有两个参数，分别为行和列，这里的infoshow只需要一个参数，
    connect(ui->table,&QTableWidget::cellClicked,this,&Widget::infrShow);
    connect(ui->add,&QPushButton::clicked,this,&Widget::addTableItem);
    connect(ui->change,&QPushButton::clicked,this,&Widget::changeTableItem);
}
Widget::~Widget()
{
    delete ui;
}
void Widget::on_color_change_stateChanged(int arg1)
{
    if(arg1==0)
    {
        ui->table->setAlternatingRowColors(false);
    }
    if(arg1==2)//未选中
    {
        ui->table->setAlternatingRowColors(true);
    }
}
void Widget::appendOneRow(QString name, QString sex, int age, QString address)
{
    int count = ui->table->rowCount();
    ui->table->setRowCount(count+1);
    QTableWidgetItem*  add_name=new QTableWidgetItem(name);
    QTableWidgetItem*  add_sex=new QTableWidgetItem(sex);
    QTableWidgetItem*  add_age=new QTableWidgetItem(QString::number(age));
    QTableWidgetItem*  add_address=new QTableWidgetItem(address);
    ui->table ->setItem(count,0,add_name);
    ui->table ->setItem(count,1,add_sex);
    ui->table ->setItem(count,2,add_age);
    ui->table ->setItem(count,3,add_address);
    add_name->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    add_sex->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    add_age->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    add_address->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
}
void Widget::on_choose_everyone_clicked()
{
    ui->table->setSelectionBehavior(QAbstractItemView::SelectItems);
}
void Widget::on_choose_line_clicked()
{
    ui->table->setSelectionBehavior(QAbstractItemView::SelectRows);
}
void Widget::on_change_everyone_stateChanged(int arg1)
{
    if(arg1==0)//未选中
    {
        ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
    if(arg1==2)
    {
        ui->table->setEditTriggers(QAbstractItemView::AllEditTriggers);
    }
}
void Widget::on_show_line_stateChanged(int arg1)
{
    if(arg1==0)//未选中
    {
        ui->table->horizontalHeader()->hide();
    }
    if(arg1==2)
    {
        ui->table->horizontalHeader()->show();
    }
}
void Widget::on_show_row_stateChanged(int arg1)
{
    if(arg1==0)//未选中
    {
        ui->table->verticalHeader()->hide();
    }
    if(arg1==2)
    {
        ui->table->verticalHeader()->show();
    }
}
void Widget::infrShow(int row)
{
    //获取每个qtablewidgetitem的内容，这里其实可以使用循环
    ui->name->setText(ui->table->item(row,0)->text());
    ui->sex->setText(ui->table->item(row,1)->text());
    ui->age->setText(ui->table->item(row,2)->text());
    ui->address->setText(ui->table->item(row,3)->text());
}
void Widget::addTableItem()
{
    QString name = ui->name->text();
    QString sex = ui->sex->text();
    int age = ui->age->text().toInt();
    QString address = ui->address->text();
    appendOneRow(name, sex, age, address);
}
void Widget::changeTableItem()
{
    //获取当前行
    int row = ui->table->currentRow();
    QTableWidgetItem* name_change    = new QTableWidgetItem(ui->name->text());
    QTableWidgetItem* sex_change     = new QTableWidgetItem(ui->sex->text());
    QTableWidgetItem* age_change     = new QTableWidgetItem(ui->age->text());
    QTableWidgetItem* address_change = new QTableWidgetItem(ui->address->text());
    ui->table->setItem(row,0,name_change);
    ui->table->setItem(row,1,sex_change);
    ui->table->setItem(row,2,age_change);
    ui->table->setItem(row,3,address_change);
    name_change->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    sex_change->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    age_change->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    address_change->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
}

void Widget::on_insert_clicked()
{
    int row = ui->table->currentRow();
    ui->table->insertRow(row);
    QTableWidgetItem* name_insert    = new QTableWidgetItem(ui->name->text());
    QTableWidgetItem* sex_insert    = new QTableWidgetItem(ui->sex->text());
    QTableWidgetItem* age_insert     = new QTableWidgetItem(ui->age->text());
    QTableWidgetItem* address_insert = new QTableWidgetItem(ui->address->text());
    ui->table->setItem(row,0,name_insert);
    ui->table->setItem(row,1,sex_insert);
    ui->table->setItem(row,2,age_insert);
    ui->table->setItem(row,3,address_insert);
    name_insert   ->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    sex_insert    ->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    age_insert    ->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    address_insert->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
}


void Widget::on_del_clicked()
{
    int row = ui->table->currentRow();
    ui->table->removeRow(row);
}

