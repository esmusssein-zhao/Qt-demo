#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QGridLayout>
#include <QUdpSocket>
#include <QTime>
#include <QFileDialog>
#include <QFile>
#include <QUdpSocket>
#include <QMessageBox>
#include <QHostAddress>
#include <QTcpSocket>
#include <QTcpServer>
#include <QElapsedTimer>
#include <QNetworkInterface>
#include <QHostInfo>
#include <QTableWidget>
#include <QTimer>
#include <algorithm>
#include <set>
#include <QVariant>
#include "readonlydelegate.h"
#include "udpthread.h"

#define TRAN_SIZE 1024;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
//send word
private:
    Ui::Widget *ui;
    QUdpSocket *p_udpSocket;
    int wordPort = 9999;
    QString sendIpAddress;
protected:
    void readData();
    void sendData();

//send big file
    //send

private slots:
    void sendFileButtonClicked();

private:
    QUdpSocket *m_udpSocket;
    qint64 sendsize;//已发送文件大小
    QString b_fileName;//文件名字
    qint64 fileSize;//文件大小
    QFile file;//file是要接收并存储的文件

    //receive
private slots:
    void slotRecv_client(char *buf, int len);
private:
    //线程对象
    UdpThread *m_udpThread;

//    QFile file;
    qint64 filesize;
    QString filename;


//send file
private:
    qint16 filePort = 8888;
    int i;
    QUdpSocket *udpSocket;
    QHostAddress severIp;
    QElapsedTimer time;
    QFile *locFile;
    QString fileName;
    QString theFileName;
    qint64 totalBytes;
    qint64 bytesWritten;
    qint64 bytesTobeWrite;
    qint64 payloadSize;
    QTcpSocket *tcpSocket;
    QTcpServer *tcpServer;
    quint16 blockSize;
    QByteArray msgn;
private slots:
//    void on_OpenBtn_clicked();
    void on_SendBtn_clicked();
//    void updClntProgress();
    void dataReceived();

//Search user & Select
private:
    int userNumber = 0;
    QUdpSocket * receiver_server;
    qint16 localPort = 11121;
    qint16 serverPort = 12811;
    void addBroadcastResItem(QByteArray data, QString ip);
    QString getIp();
    QByteArray addrCommit = "GetIPAddr";
    QUdpSocket * receiver_client;
    QUdpSocket * sender_client;
    void addIpItem(QByteArray data);
private slots:
    void processPengingDatagram();
    void processAndAddItem();

//special
private slots:
    void on_ipTableWidget_itemClicked(QTableWidgetItem *item);
private:
    void timerEvent(QTimerEvent *event) override;//update IP
    std::vector<QString> ipItemV;//Prevent ip addresses from being added repeatedly
    std::set<QString> sendIpSet;//Using vector to store the sent IP addresses is repeated
    void closeEvent(QCloseEvent *event) override;

};
#endif // WIDGET_H
