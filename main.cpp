#include "ui/wallitem.h"
#include <QApplication>
#include "engine/layout.h"
#include <QDebug>
#include "ui/canvas.h"
#include <QGraphicsScene>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Layout* l = new Layout("/home/alesapin/Code/multiagent/layouts/smallClassic.lay",30);
    qDebug() << "layout createad";
    Canvas v(l);
    v.show();
    return a.exec();
}
