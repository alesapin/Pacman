#include "pacmanitem.h"




PacmanItem::PacmanItem(QPointF pos, int cs):
    startPosition(pos),
    cellSize(cs)
{
    setBrush(QBrush(Qt::yellow));
    setRect(pos.y()*cellSize,pos.x()*cellSize,cellSize,cellSize);
}

QRectF PacmanItem::boundingRect() const
{
    return QRectF(startPosition.x(),startPosition.y(),cellSize,cellSize);
}


