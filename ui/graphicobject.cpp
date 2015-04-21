#include "graphicobject.h"
#include <QDebug>
GraphicObject::GraphicObject(QPointF start, int cs,int stepTime):
    startPosition(start),
    cellSize(cs),
    stepTime(stepTime)
{
    setPos(QPointF(startPosition.y()*cellSize,startPosition.x()*cellSize));
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(moveOneStep()));
}

QRectF GraphicObject::boundingRect() const
{
    //return QRectF(startPosition.x(),startPosition.y(),cellSize,cellSize);
    return QRectF(0,0,cellSize,cellSize);
}

void GraphicObject::moveToPoint(QPointF moveTo, Direction dir)
{
    currentTarget = convertCoordinates(moveTo);

    timer->start(stepTime);
}

GraphicObject::~GraphicObject()
{
    delete timer;
}

void GraphicObject::moveOneStep()
{
    double deltaX = currentTarget.x() - x();
    double deltaY = currentTarget.y() - y();
    if(x() != currentTarget.x() || y() != currentTarget.y()){
        this->moveBy(deltaX/5.,deltaY/5.);
    }else{
        timer->stop();
    }
}

QPointF GraphicObject::convertCoordinates(QPointF global)
{
    return QPointF(global.x()-startPosition.x(),global.y()-startPosition.y());
}
