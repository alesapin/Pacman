#include "ui/wallitem.h"
#include <QApplication>
#include "engine/layout.h"
#include <QDebug>
#include "ui/canvas.h"
#include <QGraphicsScene>
#include <cstdlib>
#include "engine/gameoptions.h"
int main(int argc, char *argv[])
{
    srand(time(0));
    QApplication a(argc, argv);
    GameOptions opts;
    opts.layoutPath = "/home/alesapin/Code/multiagent/layouts/mediumClassic.lay";
//    opts.alpha = 0.2;
//    opts.epsilon = 0.05;
//    opts.gamma = 0.8;
//    opts.numIters = 50;
    opts.minimaxDepth=3;
    opts.ghostAgent = Game::RANDOM;
    opts.pacmanAgent = Game::MINIMAX;
    Canvas v(opts,30);
    qDebug() << "layout createad";
    v.show();
    return a.exec();
}
