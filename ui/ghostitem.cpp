#include "ghostitem.h"
#include <QDebug>


GhostItem::GhostItem(QPointF pos, int cs, int timeStep,int num):
    GraphicObject(pos,cs,timeStep)
{
    counter = 0;
    textures[NORTH] = QPixmap(QString::fromStdString(":/images/"+std::to_string(num)+"n.png")).scaledToHeight(cs);
    textures[SOUTH] = QPixmap(QString::fromStdString(":/images/"+std::to_string(num)+"s.png")).scaledToHeight(cs);
    textures[WEST] = QPixmap(QString::fromStdString(":/images/"+std::to_string(num)+"w.png")).scaledToHeight(cs);
    textures[EAST] = QPixmap(QString::fromStdString(":/images/"+std::to_string(num)+"e.png")).scaledToHeight(cs);
    textures[NOACTION] = QPixmap(":/images/scarried.png").scaledToHeight(cs);
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
    currentTarget = moveTo;
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





