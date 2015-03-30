#ifndef CANVAS_H
#define CANVAS_H
#include <QWidget>
#include "wallitem.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include "gamestate.h"
#include <map>
#include "layout.h"
#include <vector>
#include <QGraphicsScene>
#include "pacmankeyboarditem.h"
#include <QTimer>
#include <QObject>
#include "pacmanitem.h"
#include "reflectagent.h"
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
    Layout* layout; //пока рисуем лейоутом, потом будем рисовать гейм стейтом
    WallItem* wallPainter;
    GameState currentGameState;
    PacmanItem* pacman;
    void removeFood(QPointF foodPoint);
    void drawFood();
    void drawWalls();
    void drawCapsules();
    void getFoodMap(std::vector<std::vector <bool> > foodTable);
    int cellSize;
    QGraphicsScene * myScene;
    QTimer * timer;
};

#endif // CANVAS_H
