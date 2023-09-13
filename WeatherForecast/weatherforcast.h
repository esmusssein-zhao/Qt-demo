#ifndef WEATHERFORCAST_H
#define WEATHERFORCAST_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QMessageBox>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui { class WeatherForcast; }
QT_END_NAMESPACE

class WeatherForcast : public QMainWindow
{
    Q_OBJECT

public:
    WeatherForcast(QWidget *parent = nullptr);
    ~WeatherForcast();
private slots:
    void onReplied(QNetworkReply* reply);
private:
    Ui::WeatherForcast *ui;
    QNetworkAccessManager* mNetworkAccessManager;
};
#endif // WEATHERFORCAST_H
