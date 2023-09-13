#include "weatherforcast.h"
#include "./ui_weatherforcast.h"

WeatherForcast::WeatherForcast(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WeatherForcast)
{
    ui->setupUi(this);
    this->setFixedSize(800,450);
    //这里使用的是WindowFlags但是不建议使用，一般使用WindowFlag
    this->setWindowFlag(Qt::FramelessWindowHint);
    mNetworkAccessManager = new QNetworkAccessManager(this);
   QUrl url("http://t.weather.itboy.net/api/weather/city/101110101");
   mNetworkAccessManager->get(QNetworkRequest(url));
   connect(mNetworkAccessManager,&QNetworkAccessManager::finished,this,&WeatherForcast::onReplied);

}

WeatherForcast::~WeatherForcast()
{
    delete ui;
}

//onReplied的标准写法
void WeatherForcast::onReplied(QNetworkReply* reply)
{
    int status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << "operation:" << reply->operation();         // 请求方式
        qDebug() << "status code:" << status_code;              // 状态码
        qDebug() << "url:" << reply->url();                     // url
        qDebug() << "raw header:" << reply->rawHeaderList();    // header
        if ( reply->error() != QNetworkReply::NoError || status_code != 200 )
        {
            QMessageBox::warning(this, "提示", "请求数据失败！", QMessageBox::Ok);
        }
        else
        {
            //获取响应信息
            QByteArray reply_data = reply->readAll();
            QByteArray byteArray  = QString(reply_data).toUtf8();
            qDebug() << "read all:" << byteArray.data();
            // parseJson()
        }
        reply->deleteLater();

}
