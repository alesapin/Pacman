#ifndef GHOSTITEM_H
#define GHOSTITEM_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QBrush>
#include "ghostagent.h"

class GhostItem : public QGraphicsRectItem
{

public:
    GhostItem(GhostAgent& agent,QPointF pos,int cs);
    QRectF boundingRect() const;
    Direction getAction(GameState& state);
private:
    GhostAgent* agent;
    QPointF startPosition;
    int cellSize;

};

#endif // GHOSTITEM_H
