#ifndef GRAPHICOBJECT_H
#define GRAPHICOBJECT_H
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QTimer>
#include <QObject>
#include "engine/configuration.h"
class GraphicObject :public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    GraphicObject(QPointF start,int cs,int stepTime);
    QRectF boundingRect() const;
    virtual void moveToPoint(QPointF moveTo,Direction dir);
    ~GraphicObject();
public slots:
    void moveOneStep();
protected:
    QPointF convertCoordinates(QPointF global);
    QPointF currentTarget;
    QTimer* timer;
    QPointF startPosition;
    int cellSize;
    int stepTime;
    QPixmap texture;
    double deltaX;
    double deltaY;
    int countStep;
};

#endif // GRAPHICOBJECT_H
