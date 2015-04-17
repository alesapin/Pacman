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
#include <QThread>
#include <unistd.h>
#include <QGraphicsView>
#include <QTimer>
#include <QObject>

class PacmanItem:public QObject,public QGraphicsEllipseItem {
        Q_OBJECT
public:
    PacmanItem(QPointF pos,int cs,QGraphicsView*);
    QRectF boundingRect() const;
    void moveToPoint(QPointF moveTo);
public slots:
    void moved();
private:
    QPointF startPosition;
    int cellSize;
    QPointF currentTarget;
    QTimer* timer;
    QPointF convertCoordinates(QPointF global);
    QGraphicsView* viewew;
};

#endif // PACMANITEM_H
