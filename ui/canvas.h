#ifndef CANVAS_H
#define CANVAS_H
#include <QWidget>
#include "wallitem.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include "engine/gamestate.h"
#include <map>
#include "engine/layout.h"
#include <vector>
#include <QGraphicsScene>
#include "pacmankeyboarditem.h"
#include <QTimer>
#include <QObject>
#include "pacmanitem.h"
#include "agents/expectimaxagent.h"
#include "ghostitem.h"
#include "agents/randomghostagent.h"
#include "agents/alphabetaagent.h"
#include "agents/rushghostagent.h"
#include "engine/game.h"
struct PointComparator {
    bool operator()(const QPointF& p1, const QPointF& p2) const {
       return  p1.x() < p2.x() ||
                          (p1.x() == p2.x() && p1.y() < p2.y());
    }
};
class Canvas:  public QGraphicsView {
        Q_OBJECT
public:
    Canvas(std::string path,int cellSize);
    void drawState(GameState* state);
public slots:
    void gameLoop();
private:
    std::map<QPointF,QGraphicsEllipseItem*,PointComparator> foodMap;
    std::map<QPointF,QGraphicsEllipseItem*,PointComparator> capsuleMap;
    //Layout* layout; //Убрать
    WallItem* wallPainter;
    //GameState* currentGameState; //Убрать
    Game* game;
    PacmanItem* pacman;
    std::vector<GhostItem*> ghosts;
    void removeFood(QPointF foodPoint);
    void getCapsuleMap(std::vector<QPointF> caps);
    void getFoodMap(std::vector<std::vector <bool> > foodTable); // Оставить без параметров
    int cellSize;
    QGraphicsScene * myScene;
    QTimer * timer;
};

#endif // CANVAS_H
