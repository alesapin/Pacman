#include "ui/wallitem.h"
#include <QApplication>
#include "engine/layout.h"
#include <QDebug>
#include "ui/canvas.h"
#include <QGraphicsScene>
#include <cstdlib>
int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    Canvas v(":/smallClassic.lay",30);
    qDebug() << "layout createad";
    v.show();
    return a.exec();
}
