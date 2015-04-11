#ifndef GHOSTITEM_H
#define GHOSTITEM_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QBrush>
#include "agents/ghostagent.h"

class GhostItem : public QGraphicsRectItem
{

public:
    GhostItem(QPointF pos,int cs);
    QRectF boundingRect() const;
private:
    QPointF startPosition;
    int cellSize;

};

#endif // GHOSTITEM_H
