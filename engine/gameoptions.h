#ifndef GAMEOPTIONS_H
#define GAMEOPTIONS_H
#include <string>
#include <QString>
#include <QGraphicsScene>
struct GameOptions
{
    std::string pacmanAgent;
    std::string ghostAgent;
    QString layoutPath;
    int numIters;
    double alpha;
    double epsilon;
    double gamma;
    int minimaxDepth;
    QGraphicsScene* scene;
};

#endif // GAMEOPTIONS_H
