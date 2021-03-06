#ifndef WALLITEM_H
#define WALLITEM_H

#include <QWidget>
#include <QPaintEvent>
#include <QColor>
#include <vector>
#include <QPainter>
#include "elempainter.h"
#include <QGraphicsItem>

class WallItem: public QGraphicsItem
{
public:
    explicit WallItem(std::vector<std::vector<bool> > w=std::vector<std::vector<bool> >(),double cs=0,QColor c=Qt::blue,double pw=-1);
    ~WallItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    std::vector<std::vector<bool> > walls;
    double cellSize;
    QColor color;
    double penWidth;
    ElemType checkCell(int i,int j);
    QPainter* painter;
    QPixmap* staticItem;
};

#endif // WALLITEM_H
