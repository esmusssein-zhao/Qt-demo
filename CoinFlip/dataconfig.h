#ifndef DATACONFIG_H
#define DATACONFIG_H

#include <QObject>
#include <QMap>
#include <QVector>

class dataConfig : public QObject
{
    Q_OBJECT
public:
    explicit dataConfig(QObject *parent = 0);
public:
    //存放每关的初始内容，用map存储，int为管卡数，QVector< QVector<int> >为关卡的数组vector
    QMap<int, QVector< QVector<int> > >mData;
signals:
public slots:
};

#endif // DATACONFIG_H
