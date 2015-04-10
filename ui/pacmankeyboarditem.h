#ifndef PACMANKEYBOARDITEM_H
#define PACMANKEYBOARDITEM_H
#include <QGraphicsEllipseItem>
#include "agents/agent.h"
#include <QKeyEvent>
#include <QRectF>
#include <algorithm>
#include <QBrush>
#include <QGraphicsItem>
#include <QVariant>
#include <QGraphicsScene>
class PacmanKeyboardItem:public QGraphicsEllipseItem

{
public:
    PacmanKeyboardItem(QPointF origin, int cellSize);
    QRectF boundingRect() const;
    Direction getAction(GameState state);
    void keyPressEvent(QKeyEvent *event);

private:
    QPointF currentPosition;
    Direction currentDirection;
    int cellSize;
};

#endif // PACMANKEYBOARDITEM_H
