#include "ui/wallitem.h"
#include <QApplication>
#include "engine/layout.h"
#include <QDebug>
#include "ui/canvas.h"
#include <QGraphicsScene>
#include <cstdlib>
#include "engine/gameoptions.h"
#include "ui/menu/mainmenu.h"
int main(int argc, char *argv[])
{
    srand(time(0));
    QApplication a(argc, argv);
    MainMenu m;
    m.show();
    return a.exec();
}
