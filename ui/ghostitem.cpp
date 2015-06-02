#include "ghostitem.h"
#include <QDebug>


GhostItem::GhostItem(QPointF pos, int cs, int timeStep,int num):
    GraphicObject(pos,cs,timeStep)
{
    counter = 0;
    textures[NORTH] = QPixmap(ResourceLoader::GHOST_TEXTURES_PATH[(num-1)%4]+"n.png").scaledToHeight(cs);
    textures[SOUTH] = QPixmap(ResourceLoader::GHOST_TEXTURES_PATH[(num-1)%4]+"s.png").scaledToHeight(cs);
    textures[WEST] = QPixmap(ResourceLoader::GHOST_TEXTURES_PATH[(num-1)%4]+"w.png").scaledToHeight(cs);
    textures[EAST] = QPixmap(ResourceLoader::GHOST_TEXTURES_PATH[(num-1)%4]+"e.png").scaledToHeight(cs);
    textures[NOACTION] = QPixmap(ResourceLoader::SCARRIED_GHOST_TEXTURE_PATH).scaledToHeight(cs);
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





