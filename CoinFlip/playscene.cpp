#include "playscene.h"

PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
{

}

PlayScene::PlayScene(int index)
{
    levalIndex=index;
    qDebug()<<"进入关卡："<<levalIndex;
    this->setWindowTitle("翻金币");
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setFixedSize(320,588);
    //获取配置信息，加载到game info中用于初始化硬币状态
    dataConfig config;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            //通过传入的关卡数来读取对应的数组
            gameInfo[i][j]=config.mData[this->levalIndex][i][j];
        }
    }

    //胜利后图片
    QLabel* winLab = new QLabel;
    QPixmap winPic;
    winPic.load(":/res/LevelCompletedDialogBg.png");
    winLab->setParent(this);
    winLab->setGeometry(0,0,winPic.width(),winPic.height());
    winLab->setPixmap(winPic);
    winLab->move((this->width()-winPic.width())*0.5,-winPic.height());

    //创建关卡格子
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            QLabel* background = new QLabel;
            background->setGeometry(0,0,50,50);
            //缺少冒号出不来！！！！！！！！
            background->setPixmap(QPixmap(":/res/BoardNode.png"));
//            background->setPixmap(QPixmap("/res/BoardNode.png"));
            background->setParent(this);
            background->move(57+i*50,200+j*50);
            //读取正反
            QString picName;
            if(gameInfo[i][j]==1)
            {
                picName=":/res/Coin0001";
            }
            else
            {
                picName=":/res/Coin0008";
            }
            //创建金币
            MyCoin* coin = new MyCoin(picName);
            coin->setParent(this);
            coin->move(59+i*50,203+j*50);
            //记录坐标和正反
            coin->x_axis=i;
            coin->y_axis=j;
            coin->ToF=gameInfo[i][j];
            coinButton[i][j]=coin;
            //点击连接
            connect(coin,&MyCoin::clicked,[=]()
            {
                coin->changeToF();
                gameInfo[i][j] = gameInfo[i][j] == 0?1:0;
                //不能放在上面连接的外部
                //点击后对周围四个进行反转
                QTimer::singleShot(300,this,[=]()
                {
                    //选择位置的右边的反转
                    if(coin->x_axis<3)
                    {
                        coinButton[coin->x_axis+1][coin->y_axis]->changeToF();
                        gameInfo[coin->x_axis+1][coin->y_axis] = gameInfo[coin->x_axis+1][coin->y_axis]==0?1:0;
                    }
                    //选择位置的左边的反转
                    if(coin->x_axis>0)
                    {
                        coinButton[coin->x_axis-1][coin->y_axis]->changeToF();
                        gameInfo[coin->x_axis-1][coin->y_axis] = gameInfo[coin->x_axis-1][coin->y_axis]==0?1:0;
                    }
                    //选择位置的下边的反转
                    if(coin->y_axis<3)
                    {
                        coinButton[coin->x_axis][coin->y_axis+1]->changeToF();
                        gameInfo[coin->x_axis][coin->y_axis+1] = gameInfo[coin->x_axis][coin->y_axis+1]==0?1:0;
                    }
                    //选择位置的上边的反转
                    if(coin->y_axis>0)
                    {
                        coinButton[coin->x_axis][coin->y_axis-1]->changeToF();
                        gameInfo[coin->x_axis][coin->y_axis-1] = gameInfo[coin->x_axis][coin->y_axis-1]==0?1:0;
                    }
                    //进入判断默认改为true
                    win=true;
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            if(coinButton[i][j]->ToF==false)
                            {
                                //如果为false，胜利条件为结束，直接结束判断
                                win=false;
                                break;
                            }
                        }
                    }
                    //判断结束返回胜利
                    if(win)
                    {
                        qDebug()<<"win!!";
                        //断开连接，lambda无法断开
//                        disconnect(coin,&MyCoin::clicked,this,nullptr);
                        for(int i=0;i<4;i++)
                        {
                              for(int j=0;j<4;j++)
                              {
                                  coinButton[i][j]->ToF=true;
                              }
                        }
                        QPropertyAnimation* animation=new QPropertyAnimation(winLab,"geometry");
                        //动画时间
                        animation->setDuration(1000);
                        //保存动画的可选起始值
                        animation->setStartValue(QRect(winLab->x(),winLab->y(),winLab->width(),winLab->height()));
                        //保存动画的结束值
                        animation->setEndValue(QRect(winLab->x(),winLab->y()+114,winLab->width(),winLab->height()));
                        //动画的缓动曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start();
                        //禁用按钮
                        for(int i=0;i<4;i++)
                        {
                           for(int j=0;j<4;j++)
                           {
                               coinButton[i][j]->isWin=true;
                           }
                        }
                    }
                });

            });

        }
    }
    QMenuBar* bar=menuBar();
    setMenuBar(bar);
    QMenu* startMenu= bar->addMenu("开始");
    QMenu* about= bar->addMenu("关于");
    QAction* quit=startMenu->addAction("退出");
    QAction* quitInfo=about->addAction("介绍");
    QLabel* leval=new QLabel(QString("LEVAL:%1").arg(levalIndex));
    leval->setGeometry(QRect(30,this->height()-50,120,50));
    QFont font("华文琥珀", 20, 50, true);
//    font.setFamily("华文琥珀");
//    font.setPointSize(20);
    leval->setFont(font);
    leval->setParent(this);
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
    //返回按钮
    BackPushButton* back = new BackPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    //设置对象树
    back->setParent(this);
    //按钮移动位置
    back->move(320-77,558);
    //返回按钮连接
    connect(back,&BackPushButton::clicked,[=]()
    {
        QTimer::singleShot(200,this,[=]()
        {
            this->hide();
            emit this->backClicked2();
            qDebug()<<"返回了关卡页面";
        });
    });   

}


//绘画事件重写
void PlayScene::paintEvent(QPaintEvent *)
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
