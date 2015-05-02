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
#include "resourceloader.h"
#include "graphicobject.h"
class PacmanItem: public GraphicObject{
public:
    PacmanItem(QPointF pos,int cs,int stepTime);
    void moveToPoint(QPointF moveTo,Direction dir);
private:
    int currentFrame;
};

#endif // PACMANITEM_H
