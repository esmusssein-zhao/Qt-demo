#include "chooselevel.h"

ChooseLevel::ChooseLevel(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowTitle("选择关卡");
    //需要使用qpixmap
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setFixedSize(320,588);
    QMenuBar* bar=menuBar();
    setMenuBar(bar);
    QMenu* startMenu= bar->addMenu("开始");
    QMenu* about= bar->addMenu("关于");
    QAction* quit=startMenu->addAction("退出");
    QAction* quitInfo=about->addAction("介绍");
    //退出窗口连接
    connect(quit,&QAction::triggered,[=]()
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
    BackPushButton* back = new BackPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    //设置对象树
    back->setParent(this);
    //按钮移动位置
    back->move(320-77,558);
    //返回按钮连接
    connect(back,&BackPushButton::clicked,[=]()
    {
//        back->backZoom1();
//        back->backZoom2();
        QTimer::singleShot(500,this,[=]()
        {
            //隐藏ChooseLevel
            this->hide();
            //触发backClicked信号，实现在一个触发事件中触发另一个信号
            emit this->backClicked1();
            qDebug()<<"返回了主页面";
        });
    });
    //创建关卡按钮，20个
    qDebug()<<"个按钮创建中！";
    for(int i=0;i<20;i++)
    {
        StartPushButton* levelButton=new StartPushButton(":/res/LevelIcon.png",":/res/LevelIcon.png");
        levelButton->setParent(this);
        levelButton->move(30+(i%4)*67.5,140+(i/4)*67.5);
        QLabel* buttonText = new QLabel;
        buttonText->setParent(this);
        buttonText->setFixedSize(levelButton->width(),levelButton->height());
        //无法使用buttonText->setText(QString(i+1));来创建文本，因为无法识别i
        buttonText->setText(QString::number(i+1));
        //对齐方式
        buttonText->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        buttonText->move(30+(i%4)*67.5,140+(i/4)*67.5);
        //设置小部件属性（默认为false），设置为穿透
        buttonText->setAttribute(Qt::WA_TransparentForMouseEvents,true);
        //关卡选择按键连接
        connect(levelButton,&StartPushButton::clicked,[=]()
        {
            //初始状态为null，直接创建新对象
            if(pSence==nullptr)
            {
                this->hide();
                //用于关卡的选择
                pSence =new PlayScene(i+1);
                pSence->show();
            }
            //此处链接
            connect(pSence,&PlayScene::backClicked2,[=]()
            {
                this->show();
                //关卡不重复使用，退出直接销毁
                delete pSence;
                pSence=nullptr;
                qDebug()<<"再次显示主菜单";
            });
        });
        //此处连接导致关卡页面无法显示,即使不对指针进行释放也无法显示，个人认为是信号连接问题（逻辑）
//        connect(pSence,&PlayScene::backClicked2,[=]()
//        {
//            this->show();
//            delete pSence;
//            pSence=nullptr;
//            qDebug()<<"再次显示主菜单";
//        });
    }

}

//绘画事件重写
void ChooseLevel::paintEvent(QPaintEvent *)
{
    //实例化画家对象，this为绘图设备
    QPainter painter(this);
    QPixmap pic;
    //使用qpixmap加载对应图片
    pic.load(":/res/OtherSceneBg.png");
    //使用画家在this设备上按照pic所加载的图片进行绘画（绘画起始位置x,y,绘画结束位置x,y,所绘对象）
    painter.drawPixmap(0,0,this->width(),this->height(),pic);
    pic.load(":/res/Title.png");
    painter.drawPixmap(25,25,pic.width(),pic.height(),pic);
}

