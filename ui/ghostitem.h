#ifndef GHOSTITEM_H
#define GHOSTITEM_H
#include <string>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QBrush>
#include "agents/ghostagent.h"
#include "graphicobject.h"
#include "resourceloader.h"
class GhostItem : public GraphicObject
{
public:
    GhostItem(QPointF pos,int cs,int timeStep,int num);
    void moveToPoint(QPointF moveTo,Direction dir);
    void scarryMode();
    void normalMode();
private:
    int counter;
    bool scar;
    std::map<Direction,QPixmap> textures;
};

#endif // GHOSTITEM_H
