#include "weatherforcast.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WeatherForcast w;
    w.show();
    return a.exec();
}
