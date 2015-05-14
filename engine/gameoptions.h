#ifndef GAMEOPTIONS_H
#define GAMEOPTIONS_H
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QSettings>
#include "ui/resourceloader.h"
#include "game.h"
struct GameOptions
{
    QString pacmanAgent;
    QString ghostAgent;
    QString layoutPath;
    int numIters;
    double alpha;
    double epsilon;
    double gamma;
    int minimaxDepth;
    int cellSize;
    int gameSpeed;
    QGraphicsScene* scene;
    static  void createDefaultCfg(QFile&);
    static GameOptions *parseFromFile();
};

#endif // GAMEOPTIONS_H
