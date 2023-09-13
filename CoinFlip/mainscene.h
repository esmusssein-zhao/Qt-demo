#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QPainter>
#include <QString>
#include "startpushbutton.h"
#include "chooselevel.h"
#include <QTimer>
#include <backpushbutton.h>

namespace Ui {
class MainScene;
}

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScene(QWidget *parent = 0);
    ~MainScene();
private:
    ChooseLevel* chooseScense=NULL;
    Ui::MainScene *ui;
    void paintEvent(QPaintEvent *);
    StartPushButton* start;
};

#endif // MAINSCENE_H
