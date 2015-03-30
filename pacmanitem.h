#ifndef PACMANITEM_H
#define PACMANITEM_H
#include <QGraphicsEllipseItem>
#include "agent.h"
#include <QKeyEvent>
#include <QRectF>
#include <algorithm>
#include <QBrush>
#include <QGraphicsItem>
#include <QVariant>
#include <QGraphicsScene>
#include "reflectagent.h"
class PacmanItem:public QGraphicsEllipseItem
{
public:
    PacmanItem(ReflectAgent& agent,QPointF pos,int cs);
    QRectF boundingRect() const;
    Direction getAction(GameState& state);
private:
    ReflectAgent* agent;
    QPointF startPosition;
    int cellSize;
};

#endif // PACMANITEM_H
