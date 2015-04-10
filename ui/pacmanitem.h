#ifndef PACMANITEM_H
#define PACMANITEM_H
#include <QGraphicsEllipseItem>
#include "agents/agent.h"
#include <QKeyEvent>
#include <QRectF>
#include <algorithm>
#include <QBrush>
#include <QGraphicsItem>
#include <QVariant>
#include <QGraphicsScene>
class PacmanItem:public QGraphicsEllipseItem
{
public:
    PacmanItem(Agent& agent,QPointF pos,int cs);
    QRectF boundingRect() const;
    Direction getAction(GameState& state);
private:
    Agent* agent;
    QPointF startPosition;
    int cellSize;
};

#endif // PACMANITEM_H
