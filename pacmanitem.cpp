#include "pacmanitem.h"




PacmanItem::PacmanItem(ReflectAgent &agent, QPointF pos, int cs):
    agent(&agent),
    startPosition(pos),
    cellSize(cs)
{
    setBrush(*(new QBrush(Qt::yellow)));
    setRect(pos.y()*cellSize,pos.x()*cellSize,cellSize,cellSize);
}

QRectF PacmanItem::boundingRect() const
{
    return QRectF(startPosition.x(),startPosition.y(),cellSize,cellSize);
}

Direction PacmanItem::getAction(GameState& state)
{
    return agent->getAction(state);
}
