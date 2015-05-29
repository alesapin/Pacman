#include "ui/wallitem.h"
#include <QApplication>
#include "engine/layout.h"
#include <QDebug>
#include "ui/canvas.h"
#include <QGraphicsScene>
#include <cstdlib>
#include "ui/menu/mainmenu.h"
#include "ui/resourceloader.h"
#include "ui/levelCreator/field.h"
#include "ui/levelCreator/levelcreator.h"
#include <tbb/task_scheduler_init.h>
int main(int argc, char *argv[])
{
    srand(time(0));
    tbb::task_scheduler_init init;  // Automatic number of threads

    QApplication a(argc, argv);
    ResourceLoader::load();
    MainMenu m;
    m.show();
    return a.exec();
}
