#include "ghostitem.h"
#include <QDebug>


GhostItem::GhostItem(QPointF pos, int cs, int timeStep,int num):
    GraphicObject(pos,cs,timeStep)
{
    counter = 0;
    textures[NORTH] = QPixmap(QString::fromStdString(":/textures/textures/"+std::to_string((num%4)+1)+"n.png")).scaledToHeight(cs);
    textures[SOUTH] = QPixmap(QString::fromStdString(":/textures/textures/"+std::to_string((num%4)+1)+"s.png")).scaledToHeight(cs);
    textures[WEST] = QPixmap(QString::fromStdString(":/textures/textures/"+std::to_string((num%4)+1)+"w.png")).scaledToHeight(cs);
    textures[EAST] = QPixmap(QString::fromStdString(":/textures/textures/"+std::to_string((num%4)+1)+"e.png")).scaledToHeight(cs);
    textures[NOACTION] = QPixmap(":/textures/textures/scarried.png").scaledToHeight(cs);
    scar = false;
    texture = textures[NORTH];
    setPixmap(texture.copy(0,0,cs,cs));
}

void GhostItem::moveToPoint(QPointF moveTo, Direction dir)
{
    if(!scar) {
            texture = textures[dir];
    }
    setPixmap(texture.copy(counter*cellSize,0,cellSize,cellSize));
    if(currentTarget != moveTo){
        setPos(currentTarget);
        timer->stop();
        currentTarget = moveTo;
    }
    timer->start(stepTime);
    counter = (counter+1)%2;
}

void GhostItem::scarryMode()
{
    texture = textures[NOACTION];
    scar = true;
}

void GhostItem::normalMode()
{
    scar = false;
}





