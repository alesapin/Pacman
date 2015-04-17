#include "pacmanitem.h"
#include <QDebug>



PacmanItem::PacmanItem(QPointF pos, int cs, QGraphicsView *v):
    cellSize(cs)
{
    setBrush(QBrush(Qt::yellow));
    viewew = v;

    startPosition = QPointF(pos.y()*cellSize,pos.x()*cellSize);
    setRect(startPosition.x(),startPosition.y(),cellSize,cellSize);
    timer = new QTimer(viewew);
    connect(timer,SIGNAL(timeout()),this,SLOT(moved()));
}

QRectF PacmanItem::boundingRect() const
{
    return QRectF(startPosition.x(),startPosition.y(),cellSize,cellSize);
}

void PacmanItem::moveToPoint(QPointF moveTo)
{
    currentTarget = convertCoordinates(moveTo);
    timer->start(1);
}

void PacmanItem::moved()
{
    double deltaX = currentTarget.x() - x();
    double deltaY = currentTarget.y() - y();
    if(x() != currentTarget.x() || y() != currentTarget.y()){
        this->moveBy(deltaX/4.,deltaY/4.);
    }else{
        timer->stop();
    }
}


QPointF PacmanItem::convertCoordinates(QPointF global)
{
    return QPointF(global.x()-startPosition.x(),global.y()-startPosition.y());
}


