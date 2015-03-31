#include "pacmankeyboarditem.h"
#include <QDebug>




PacmanKeyboardItem::PacmanKeyboardItem(QPointF origin, int cellSize):
    currentPosition(origin),
    cellSize(cellSize)
{
    setBrush(*(new QBrush(Qt::yellow)));
    setRect(origin.y()*cellSize,origin.x()*cellSize,cellSize,cellSize);
    currentDirection = STOP;
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

QRectF PacmanKeyboardItem::boundingRect() const
{
    return QRectF(currentPosition.x(),currentPosition.y(),cellSize,cellSize);
}

Direction PacmanKeyboardItem::getAction(GameState state)
{
    return currentDirection;
}

void PacmanKeyboardItem::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left){
        currentDirection = WEST;
    }else if (event->key() == Qt::Key_Right) {
        currentDirection = EAST;
    }else if (event->key() == Qt::Key_Up) {
        currentDirection = NORTH;
    }else if (event->key() == Qt::Key_Down){
        currentDirection = SOUTH;
    }
}



