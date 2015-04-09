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
#include "engine/randomghostagent.h"
struct PointComparator {
    bool operator()(const QPointF& p1, const QPointF& p2) const {
       return  p1.x() < p2.x() ||
                          (p1.x() == p2.x() && p1.y() < p2.y());
    }
};
class Canvas:  public QGraphicsView {
        Q_OBJECT
public:
    Canvas(Layout* layout);
    void drawStaticContent();
    void drawMoving();
public slots:
    void gameLoop();
private:
    std::map<QPointF,QGraphicsEllipseItem*,PointComparator> foodMap;
    std::map<QPointF,QGraphicsEllipseItem*,PointComparator> capsuleMap;
    Layout* layout; //пока рисуем лейоутом, потом будем рисовать гейм стейтом
    WallItem* wallPainter;
    GameState* currentGameState;
    PacmanItem* pacman;
    std::vector<GhostItem*> ghosts;
    void removeFood(QPointF foodPoint);
    void drawFood();
    void drawWalls();
    void drawGhosts();
    void getCapsuleMap();
    void getFoodMap(std::vector<std::vector <bool> > foodTable);
    int cellSize;
    QGraphicsScene * myScene;
    QTimer * timer;
    int currentMover;
};

#endif // CANVAS_H
