#include "ghostitem.h"
#include <QDebug>


GhostItem::GhostItem(QPointF pos, int cs):
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



