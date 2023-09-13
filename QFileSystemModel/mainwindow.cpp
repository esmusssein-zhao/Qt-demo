#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QFileSystemModel(this);
    model->setRootPath(QDir::currentPath());
    ui->treeView->setModel(model);
    ui->listView->setModel(model);
    ui->tableView->setModel(model);
    connect(ui->treeView,&QTableView::clicked,ui->listView,&QListView::setRootIndex);
    connect(ui->treeView,&QTreeView::clicked,ui->tableView,&QTableView::setRootIndex);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{

}
