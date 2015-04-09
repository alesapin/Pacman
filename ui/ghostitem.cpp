#include "ghostitem.h"
#include <QDebug>


GhostItem::GhostItem(GhostAgent &agent, QPointF pos, int cs):
    agent(&agent),
    startPosition(pos),
    cellSize(cs)
{
    setBrush(QBrush(Qt::red));
    setRect(pos.y()*cellSize,pos.x()*cellSize,cellSize,cellSize);
}

QRectF GhostItem::boundingRect() const
{
    return QRectF(startPosition.x(),startPosition.y(),cellSize,cellSize);
}

Direction GhostItem::getAction(GameState &state)
{
    return agent->getAction(state);
}

