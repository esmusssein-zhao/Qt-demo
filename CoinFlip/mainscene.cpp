#include "mainscene.h"
#include "ui_mainscene.h"


MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //点击“退出”事件
    connect(ui->actionexit,&QAction::triggered,[=]()
    {
        //在栈区创建对象，并对box进行初始化
        QMessageBox box(QMessageBox::Question, "警告", "你确定要离开吗");
        //为box添加可选择的按钮
        box.setStandardButtons(QMessageBox::Yes|QMessageBox::Cancel);
        //修改默认的文字
        box.setButtonText(QMessageBox::Yes,QString("忍心离开"));
        box.setButtonText(QMessageBox::Cancel,QString("留下"));
        //接收点击后box的值；将对话框显示为一个模态对话框，直到用户关闭它为止
        int ret = box.exec();
        if(ret==QMessageBox::Yes)
        {
            this->close();
        }
    });
    //创建选择界面
    ChooseLevel* chooseScense=new ChooseLevel;
    //创建开始按钮对象
    StartPushButton* start = new StartPushButton(":/res/MenuSceneStartButton.png");
    //设置对象树
    start->setParent(this);
    //按钮移动位置
    start->move(this->width()*0.3,this->height()*0.7);
    //开始按钮事件
    connect(start,&StartPushButton::clicked,[=]()
    {
        qDebug()<<"点击了开始按钮";
        start->zoom1();
        start->zoom2();
        //延迟显示和隐藏，为展示动画效果
        QTimer::singleShot(500,this,[=]()
        {
            //隐藏窗口
            this->hide();
            chooseScense->show();
        });
    });
    //链接的信号发送者和发送信号要为同一个对象，一个应该为创建的对象（指针），另一个为创建对象的类的signals
    //与chooselevel中的信号相连，触发后显示主菜单
    connect(chooseScense,&ChooseLevel::backClicked1,[=]()
    {
        this->show();
        qDebug()<<"再次显示主菜单";
    });
}

//添加背景  重写绘图事件void paintEvent(自动补齐)
void MainScene::paintEvent(QPaintEvent *)
{
    //实例化画家对象，this为绘图设备
    QPainter painter(this);
    QPixmap pic;
    //使用qpixmap加载对应图片
    pic.load(":/res/PlayLevelSceneBg.png");
    //使用画家在this设备上按照pic所加载的图片进行绘画（绘画起始位置x,y,绘画结束位置x,y,所绘对象）
    painter.drawPixmap(0,0,this->width(),this->height(),pic);
    pic.load(":/res/Title.png");
    painter.drawPixmap(0,25,pic.width()*0.5,pic.height()*0.5,pic);


}

MainScene::~MainScene()
{
    delete ui;
}
