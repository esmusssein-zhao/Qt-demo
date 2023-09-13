#include "widget.h"
#include "ui_widget.h"

#define TRY_TIMES 1

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{

    //set ui
    ui->setupUi(this);
    this->resize(265,282);
    this->move(200,300);
    this->setWindowTitle("my transmission");
    //tablewidget header
    QStringList header;
    header <<"ip"<<"username";
    ui->ipTableWidget->setColumnCount(header.size());
    ui->ipTableWidget->setHorizontalHeaderLabels(header);
    ui->ipTableWidget->setRowCount(0);
    ui->ipTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->ipTableWidget->setAlternatingRowColors(true);//Editing starts when an item is double clicked.
    ui->ipTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//QAbstractItemView::SelectItems 0:Select cell;QAbstractItemView::SelectRows 1:Select the row where the cell resides
    ui->ipTableWidget->setSelectionMode(QAbstractItemView::MultiSelection);//QAbstractItemView::MultiSelection 2:Multi-line selection, the mouse click can select multiple lines
    ui->ipTableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->sendWordBox->setPlaceholderText(tr("Please select Send user and enter what you want to send here"));
    //Disallow the first column of qtablewidget to be modified, based on readonlydelegate
    ReadOnlyDelegate* readOnlyDelegate = new ReadOnlyDelegate(this);
    ui->ipTableWidget->setItemDelegateForColumn(0, readOnlyDelegate);
    ui->SendBtn->setEnabled(false);
    ui->sendButton->setEnabled(false);

    //search user:start
    receiver_server = new QUdpSocket(this);
    //Binding, where the first parameter is the port number and the second allows other addresses to link to the broadcast
    receiver_server->bind(serverPort,QUdpSocket::ShareAddress);
    receiver_client = new QUdpSocket(this);
    //Binding, where the first parameter is the port number and the second indicates that other addresses are allowed to link to the broadcast
    receiver_client->bind(localPort,QUdpSocket::ShareAddress);
    connect(receiver_client,SIGNAL(readyRead()),this,SLOT(processAndAddItem()));
    //readyRead:Send this signal whenever a datagram arrives
    connect(receiver_server,SIGNAL(readyRead()),this,SLOT(processPengingDatagram()));
    QByteArray datagram = addrCommit;
    int times = TRY_TIMES;
    while(times--)
    {
        receiver_client->writeDatagram(datagram.data(),datagram.size(),QHostAddress::Broadcast,serverPort);
    }
    //update user time
    startTimer(1000);
    //search user:end

//    tcpSocket = new QTcpSocket(this);
    tcpServer = new QTcpServer(this);
//    udpSocket = new QUdpSocket(this);

    //bind port
    udpSocket->bind(filePort);
    p_udpSocket=new QUdpSocket(this);
    p_udpSocket->bind(QHostAddress::AnyIPv4,wordPort);
    tcpSocket->connectToHost(sendIpAddress,filePort);

    //show ip
    QString strIpAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // Use a QList to store all the IP addresses of the machine
    // The computer has two virtual machine IP addresses, one wireless NIC IP address and one wired NIC IP address
    // The IP address of the wireless NIC is in the third place on the List, where 1 indicates the local NIC and IP 2 indicates the wireless NIC
    strIpAddress = ipAddressesList.at(1).toString();
    ui->Current_IP->setText(strIpAddress);
    qDebug() << "Current IP set success!";

    //get this machine hostname
    QString hostname = QHostInfo::localHostName();
    ui->HostName->setText(hostname);
    qDebug() << "HostName get success!";

    //connect
    connect(p_udpSocket,&QUdpSocket::readyRead,this,&Widget::readData);
    connect(ui->sendButton,&QPushButton::clicked,this,&Widget::sendData);
    connect(ui->closeButton,&QPushButton::clicked,[=]()
    {
        this->close();
    });


//    connect(tcpSocket,&QIODevice::readyRead,this,[=](){
//      while(tcpSocket->bytesAvailable()>0)
//      {
//          QByteArray datagram;
//          datagram.resize(tcpSocket->bytesAvailable());
//          tcpSocket->read(datagram.data(),datagram.size());
//          QString msg=datagram.data();
//          if(msg == "ok")
//          {
//              updClntProgress();
//          }
//      }
//  });

//    //send file start
//      i = 0;
//      msgn.append("ok");
//      tcpServer->listen(QHostAddress::Any,filePort);
//      connect(udpSocket,&QIODevice::readyRead,this,&Widget::dataReceived);
//    //send file end

      //send big file
      m_udpSocket = new QUdpSocket(this);
      sendsize=0;
      m_udpSocket->setSocketOption(QAbstractSocket::SendBufferSizeSocketOption,8*1024*1024);
      m_udpSocket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption,500000);
      connect(ui->OpenBtn,&QPushButton::clicked,this,&Widget::sendFileButtonClicked);

      m_udpThread = new UdpThread(this);
      //sigRecvok:线程完成——读取结束的信号
      //信号传来了数据char
      connect(m_udpThread, SIGNAL(sigRecvOk(char*,int)), this, SLOT(slotRecv_client(char*,int)));
      m_udpThread->start();
      qDebug("OK");

}

Widget::~Widget()
{
    //You can also implement offline notifications here
    delete ui;
}

void Widget::Widget::readData()
{
    //Gets the sender's IP and port number and the datagram content
    char array[1024];
    QHostAddress m_ip;
    quint16 m_port;
    qint64 m_len=p_udpSocket->readDatagram(array,sizeof(array),&m_ip,&m_port);
    qDebug() << array;
    QString info(array);
    int index = info.indexOf("!@#$");
    if(-1 != index)
    {
        QString infoDo = info.mid(0, index);
        //Group packet
        if(m_len>0)
        {
            //Gets the line number of the corresponding ip address
            QList <QTableWidgetItem *> item = ui->ipTableWidget->findItems(m_ip.toString(), Qt::MatchContains);
            //this code“ui->ipTableWidget->item(item[0]->row(),1)->text()”means ：Display the corresponding name
//            QString str=QString("[%1]:%2").arg(ui->ipTableWidget->item(item[0]->row(),1)->text()).arg(array);
            QString str=QString("[%1]:").arg(ui->ipTableWidget->item(item[0]->row(),1)->text()) +infoDo;
            //dont know this is what to do
//            array[m_len]='\0';

            //Sets the text area content
            ui->sendWordBox->append(str);
        }
    }
}

void Widget::Widget::sendData()
{
    QString str= ui->sendWordBox->toPlainText() + "!@#$";
    // Write data to the communication socket
    // The message is sent to the corresponding ip address
    for(const QString& accept : sendIpSet)
    {
        p_udpSocket->writeDatagram(str.toUtf8(),QHostAddress(accept),wordPort);
    }
}

//void Widget::on_OpenBtn_clicked()
//{
//    //Opens a file and initializes file transfer parameters
//    fileName = QFileDialog::getOpenFileName(this);
//    if(!fileName.isEmpty())
//    {
//        theFileName = fileName.right(fileName.size() - fileName.lastIndexOf('/')-1);
//        ui->chlabel->setText(tr("send file name：%1 ").arg(theFileName));
//    }
//    i=0;
//    payloadSize = 60*1024;
//    totalBytes     = 0;
//    bytesWritten   = 0;
//    bytesTobeWrite = 0;
//    ui->progressBar->reset();
//    ui->SendBtn->setEnabled(true);
//}

//void Widget::on_SendBtn_clicked()
//{
//    ui->SendBtn->setText(tr("sending..."));
//    sendinit();
//    ui->SendBtn->setEnabled(false);
//}

void Widget::on_SendBtn_clicked()
{
    for(const QString& acceptIp : sendIpSet)
    {
        ui->SendBtn->setText(tr("sending..."));
        ui->chlabel->setText(tr("Start transferring file %1 ！").arg(theFileName));

        locFile = new QFile(fileName);
        if(!locFile->open((QFile::ReadOnly))){
            QMessageBox::warning(this, tr("program"), tr("can not open file %1:\n%2").arg(fileName).arg(locFile->errorString()));
            return;
        }
        totalBytes = locFile->size();
        //Start the clock
        time.start();
        bytesTobeWrite = totalBytes;

            qDebug() <<"send to" + acceptIp;
            //Update the progress bar and send files
            if(!locFile->atEnd())
            {
                QByteArray outBlock;
                outBlock = locFile->read(qMin(bytesTobeWrite, payloadSize));
                udpSocket->writeDatagram(outBlock,outBlock.length(),QHostAddress(acceptIp),filePort);
                i++;
                qDebug()<< "send over!"<< i << outBlock.size();
                bytesTobeWrite -= (int)outBlock.size();
                bytesWritten   += (int)outBlock.size();
                ui->progressBar->setMaximum(totalBytes);
                ui->progressBar->setValue(bytesWritten);

                float useTime = time.elapsed();
                double speed = bytesWritten / useTime;
                ui->chlabel->setText(tr("send %1MB (%2MB/s) \n total%3MB used time:%4s\n surplus：%5s")
                                     .arg(bytesWritten / (1024*1024))
                                     .arg(speed*1000 / (1024*1024), 0, 'f', 2)
                                     .arg(totalBytes / (1024 * 1024))
                                     .arg(useTime/1000, 0, 'f', 0)
                                     .arg(totalBytes/speed/1000 - useTime/1000, 0, 'f', 0));
            }
            if(bytesWritten == totalBytes)
            {
                qDebug() <<"send success(compare success)";
                locFile->close();
                ui->chlabel->setText(tr("send %1 success").arg(theFileName));
                ui->SendBtn->setText(tr("send"));
            }

        qDebug() <<"send process end";
        ui->SendBtn->setEnabled(false);
    }
}

//void Widget::updClntProgress()
//{
//    for(const QString& acceptIp : sendIpSet)
//    {
//        //Update the progress bar and send files
//        if(!locFile->atEnd())
//        {
//            QByteArray outBlock;
//            outBlock = locFile->read(qMin(bytesTobeWrite, payloadSize));
//            udpSocket->writeDatagram(outBlock,outBlock.length(),QHostAddress(acceptIp),filePort);
//            i++;
//            qDebug()<< "send over!"<< i << outBlock.size();
//            bytesTobeWrite -= (int)outBlock.size();
//            bytesWritten   += (int)outBlock.size();
//            ui->progressBar->setMaximum(totalBytes);
//            ui->progressBar->setValue(bytesWritten);

//            float useTime = time.elapsed();
//            double speed = bytesWritten / useTime;
//            ui->chlabel->setText(tr("send %1MB (%2MB/s) \n total%3MB used time:%4s\n surplus：%5s")
//                                 .arg(bytesWritten / (1024*1024))
//                                 .arg(speed*1000 / (1024*1024), 0, 'f', 2)
//                                 .arg(totalBytes / (1024 * 1024))
//                                 .arg(useTime/1000, 0, 'f', 0)
//                                 .arg(totalBytes/speed/1000 - useTime/1000, 0, 'f', 0));
//        }
//        if(bytesWritten == totalBytes)
//        {
//            qDebug() <<"send success(compare success)";
//            locFile->close();
//            ui->chlabel->setText(tr("send %1 success").arg(theFileName));
//            ui->SendBtn->setText(tr("send"));
//        }
//        qDebug() <<"send process end";
//    }
//}

void Widget::dataReceived()
{
    qDebug() <<"enter dataReceived function";
    while (udpSocket->hasPendingDatagrams())
    {
       QByteArray inBlock;
       inBlock.resize(udpSocket->pendingDatagramSize());

       int btn = QMessageBox::information(this,tr("Acceptance of document"),tr("Whether to accept the sent file?"),QMessageBox::Yes,QMessageBox::No);
       if (btn == QMessageBox::Yes)
       {
           QString name = QFileDialog::getSaveFileName(0,tr("Save file"));
           locFile = new QFile(name);
       }
       else
       {
            return;
       }

        if(!locFile->open(QFile::WriteOnly))
        {
            QMessageBox::warning(this,tr("Application program"),tr("Unable to read file :\n%2.").arg(locFile->errorString()));
            return;
        }
        udpSocket->readDatagram(inBlock.data(), inBlock.size());
        locFile->write(inBlock.data(),inBlock.size());
        i++;
        if(inBlock.size()<60*1024)
        {
            locFile->close();
            return;
        }
        tcpSocket->write(msgn,msgn.length());
    }
}
//send end function

//Search user function
void Widget::processPengingDatagram()
{
    QHostAddress client_address;
    //The datagram is not empty
    while( receiver_server->hasPendingDatagrams() )
    {
        quint16 recPort = 0;
        QByteArray datagram;
        //The datagram size is the size of the datagram waiting to be processed before data is collected.
        datagram.resize( receiver_server->pendingDatagramSize() );
        //Receiving datagram
        receiver_server->readDatagram(datagram.data(),datagram.size(), &client_address, &recPort);
        QString strData= datagram;
        int ret = strData.compare(addrCommit);
        if (0 == ret)
        {
            // Get the current host name
            QString hostname = QHostInfo::localHostName();
            //Used to obtain the host name
            QByteArray datagback = (getIp() + "!@#$" + hostname).toLatin1();
//            qDebug()<<client_address<<"receive inline info";
            receiver_server->writeDatagram(datagback,datagback.size(),client_address,recPort);
        }
        //这部分应该没用
//        else
//        {
//            qDebug()<<"+++++++++++++++++++++++";
//            int index = strData.indexOf("#PROCESS-IS-CLOSE#");
//            qDebug()<<strData;
//            qDebug()<<index;
//            if(-1 != index)
//            {
//                QString closeIp = strData.mid(0, index);
//                qDebug()<<closeIp;
//                sendIpSet.erase(closeIp);
//                for(auto iter=ipItemV.begin();iter!=ipItemV.end();iter++)
//                {
//                    if(*iter == closeIp)
//                    {
//                        ipItemV.erase(iter);
//                        break;
//                    }
//                }
//                QList <QTableWidgetItem *> item = ui->ipTableWidget->findItems(closeIp, Qt::MatchContains);
//                qDebug()<<item[0]->row();
//                ui->ipTableWidget->removeRow(item[0]->row());

//                qDebug()<<"user is close this!";
//            }
//        }
    }
}

void Widget::processAndAddItem()
{
    //The datagram is not empty
    while( receiver_client->hasPendingDatagrams() )
    {
        QByteArray datagram;
        //The datagram size is the size of the datagram waiting to be processed before data is collected.
        datagram.resize( receiver_client->pendingDatagramSize() );
        //Receiving datagram
        receiver_client->readDatagram(datagram.data(),datagram.size());
        //A message was received, but it was a program shutdown alert
        int index = datagram.indexOf("#PROCESS-IS-CLOSE#");
        if(-1 != index)
        {
            QString closeIp = datagram.mid(0, index);
            qDebug()<<closeIp;
            sendIpSet.erase(closeIp);
            for(auto iter=ipItemV.begin();iter!=ipItemV.end();iter++)
            {
                //Removes the specified ip address from the vector
                if(*iter == closeIp)
                {
                    ipItemV.erase(iter);
                    break;
                }
            }
            QList <QTableWidgetItem *> item = ui->ipTableWidget->findItems(closeIp, Qt::MatchContains);
            qDebug()<<item[0]->row();
            ui->ipTableWidget->removeRow(item[0]->row());

            qDebug()<<"user is close this!";
        }
        //The ip is received
        if(-1 == index)
        {
            addIpItem(datagram);
        }
        else
        {
            qDebug() <<"Transmission error";
        }
    }
}

QString Widget::getIp()
{
    //Use the allAddresses command to get all the ip addresses
        QList<QHostAddress> list=QNetworkInterface::allAddresses();
        foreach (QHostAddress address,list)
        {
            if(address.protocol()==QAbstractSocket::IPv4Protocol)
                return address.toString();
        }
        return 0;
}

void Widget::addIpItem(QByteArray data)
{
    int index = data.indexOf("!@#$");
    QString host = data.mid(index+4);
    QString ip = data.mid(0,index);
    if (std::find(ipItemV.begin(),ipItemV.end(),ip) == ipItemV.end())
    {
        ipItemV.emplace_back(ip);

        //TableWidgett add
        int index = ui->ipTableWidget->rowCount();
        ui->ipTableWidget->insertRow(index);
        ui->ipTableWidget->setItem(index,0,new QTableWidgetItem(QString(ip)));
        ui->ipTableWidget->setItem(index,1,new QTableWidgetItem(QString(host)));
    }
    else
    {
        ;//If this already exists, we don't do it
    }
}

void Widget::timerEvent(QTimerEvent *event)
{
    if(event->timerId())
    {
        QByteArray datagram = addrCommit;
        int times = TRY_TIMES;
        while(times--)
        {
            receiver_client->writeDatagram(datagram.data(),datagram.size(),QHostAddress::Broadcast,serverPort);
        }
//        qDebug() << "update user!";
    }
}

void Widget::closeEvent(QCloseEvent *event)
{
    //event does not need to be used
    //The content is sent when the window is closed, and can also be placed in the destructor
    QByteArray datagback = getIp().toLatin1() + "#PROCESS-IS-CLOSE#";
    qDebug() <<datagback;
    qDebug()<<"1";
    for(auto& ip : ipItemV)
    {
        qDebug()<<ip;
        receiver_server->writeDatagram(datagback,datagback.size(),QHostAddress(ip),localPort);
        qDebug() <<"close info send ok";
    }
    qDebug() << "windows clsoe";
}

void Widget::on_ipTableWidget_itemClicked(QTableWidgetItem *item)
{
    //item does not need to be used
    //Do not click to obtain the content directly. Otherwise, the selected content cannot be obtained after being deselected
    sendIpSet.clear();
    QModelIndexList list = ui->ipTableWidget->selectionModel()->selectedRows();
    int count = list.count();
//    qDebug() << count;
    qDebug() << "your choose is：";
    if(count)
    {
        ui->SendBtn->setEnabled(true);
        ui->sendButton->setEnabled(true);
        for(int i =0 ; i<count ;i++)
        {
            //There is no need to determine the returned pair
            sendIpSet.emplace(ui->ipTableWidget->item(list.at(i).row(),0)->text());
            qDebug() << ui->ipTableWidget->item(list.at(i).row(),0)->text();
        }
//        qDebug() << "update send object!";
    }
    else
    {
        ui->SendBtn->setEnabled(false);
        ui->sendButton->setEnabled(false);
    }
}

void Widget::sendFileButtonClicked()
{
//         QFile file("C:\\Users\\yi.yangzhao\\Desktop\\file\\12.7z");


         //Opens a file and initializes file transfer parameters
         b_fileName = QFileDialog::getOpenFileName(this);
         if(b_fileName.isEmpty())
         {
             qDebug("file name is empty");
         }
         QString theFileName = b_fileName.right(b_fileName.size() - b_fileName.lastIndexOf('/')-1);
         ui->chlabel->setText(tr("send file name：%1 ").arg(theFileName));
         QFile file(b_fileName);


         if (!file.open(QIODevice::ReadOnly))return;
         //包1024=包头28(7个整形)+数据（996）
         char *m_sendBuf = new char[1024];
         //size:文件大小
         int size = file.size();
         qDebug()<<"文件大小"<<size;
         //num:数据包数量
         int num = 0;
         //count：数据包序号
         int count = 0;
         //最后一个包的大小
         int endSize = size%996;
         if (endSize == 0) {
             num = size/996;
         }
         else {
             num = size/996+1;//num:包的数量
         }
         qint64 len = 0;//记录发送数据

//         //一、发送文件信息
//         //1.获取文件路径
//         QString filepath = "D:/3.ts";
//         //2.获取文件信息
//         QFileInfo info(filepath);
//         fileName = info.fileName();

//         fileSize = info.size();
//         //3.设置文件名
//         file.setFileName(filepath);

         //二、发送数据
         //1、组包：28字节包头+996字节数据
         //2、发送：广播到port：65522
         while (count < num) {
             //初始化：将m_sendBuf的前1024个字符置0
             memset(m_sendBuf, 0, 1024);
             //包的结构体
             ImageFrameHead mes;
             //功能码24
             mes.funCode = 24;
             //包头长度=4*7=28
             mes.uTransFrameHdrSize = sizeof(ImageFrameHead);
             if ((count+1) != num) {
                 //数据长度
                 mes.uTransFrameSize = 996;

             }
             else {
                 //最后一个包的长度
                 mes.uTransFrameSize = endSize;
             }
             //qDebug()<<size;
             //数据帧总大小=文件大小
             mes.uDataFrameSize = size;
             //包个数
             mes.uDataFrameTotal = num;
             //包序号
             mes.uDataFrameCurr = count+1;
             //数据996的整数倍
             mes.uDataInFrameOffset = count*(1024 - sizeof(ImageFrameHead));
             qDebug()<<"uDataInFrameOffset"<<mes.uDataInFrameOffset;
             //读取文件，参数1：存储位置——指针，参数2：maxsize
             //参数1：意思是指向m_sendBuf向后移28位的位置，将996位的数据存在这里
             //从文件里读取996字节数据写入m_sendBuf数据包里数据的位置
             // data:file(996字节)->m_sendBuf(29字节起-1024字节)
             len = file.read(m_sendBuf+sizeof(ImageFrameHead), 1024-sizeof(ImageFrameHead));
             sendsize+=len;
             qDebug()<<"已发送文件大小"<<sendsize;
             //从mes里复制28个字节给m_sendBuf，mes:包头结构体。
             //构建包：m_sendBuf的前28字节写包的信息。
             memcpy(m_sendBuf, (char *)&mes, sizeof(ImageFrameHead));
             //发数据：m_sendBuf即包。
             //参数2：包的长度=表头+数据=1024，最后一个包不一定
             m_udpSocket->writeDatagram(m_sendBuf, mes.uTransFrameSize+mes.uTransFrameHdrSize, QHostAddress("192.168.148.111"), 65522);
             //currentTime:返回当前时间
             //addMSecs:返回QTime对象dieTime，其时间比当前时间延后1ms
             //dieTime = 当前时间 + 1ms
             QTime dieTime = QTime::currentTime().addMSecs(1);
             //防止卡死，隔一段时间检查有没有未完成操作
             while( QTime::currentTime() < dieTime )
                 QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
             count++;
         }
         qDebug()<<"数据发送完成";
         file.close();
         QTime dieTime = QTime::currentTime().addMSecs(10);
         while( QTime::currentTime() < dieTime )
             QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
         //qDebug("ok");
}

void Widget::slotRecv_client(char *buf, int len)
{

    qDebug() <<"enter dataReceived function";
    int btn = QMessageBox::information(this,tr("Acceptance of document"),tr("Whether to accept the sent file?"),QMessageBox::Yes,QMessageBox::No);
    if (btn == QMessageBox::Yes)
    {
        QString name = QFileDialog::getSaveFileName(0,tr("Save file"));
//        locFile = new QFile(name);
        file.setFileName(name);
    }
    else
    {
        //do not receive file
         return;
    }


//    file.setFileName("copy.7z");

    filesize = len;
    file.resize(filesize);

    bool isOK = file.open(QIODevice::WriteOnly);//isOK:文件成功打开标志
    qDebug()<<isOK;
    if(!isOK)
    {
        QMessageBox::warning(this,tr("Application program"),tr("Failed to open the file flag!"));
        return;
    }
    qint64 write_len=file.write(buf,len);
    qDebug()<<"client：写入文件的大小"<<write_len;
    qDebug()<<"filesize="<<len;

//    QPixmap pixmap;
//    pixmap.loadFromData((uchar*)buf, len, "ts");
//    ui->label->setPixmap(pixmap);
    file.close();
}
