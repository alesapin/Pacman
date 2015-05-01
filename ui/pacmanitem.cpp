#include "pacmanitem.h"
#include <QDebug>





PacmanItem::PacmanItem(QPointF pos, int cs, int stepTime):
    GraphicObject(pos,cs,stepTime),
    currentFrame(0)
{
    texture = QPixmap(":/textures/textures/pacman-sprite.png").scaledToHeight(cs);
    setPixmap(texture.copy(0,0,cellSize,cellSize));
    setTransformOriginPoint(cs/2.,cs/2.);
}


void PacmanItem::moveToPoint(QPointF moveTo,Direction dir)
{

    switch(dir){
        case NORTH:
            setRotation(270);
            break;
       case SOUTH:
            setRotation(90);
            break;
       case EAST:
            setRotation(0);
            break;
      case WEST:
            setRotation(180);
            break;
       case STOP:
            break;
    }
    if(currentTarget != moveTo){
        setPos(currentTarget);
        timer->stop();
        currentTarget = moveTo;
    }
    setPixmap(texture.copy(currentFrame*cellSize,0,cellSize,cellSize));
    currentFrame=(currentFrame+1)%5;
    timer->start(stepTime);
}



