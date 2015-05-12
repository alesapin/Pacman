#include "netscene.h"



NetScene::NetScene(int w, int h, int cellSize,QObject *parent):
    QGraphicsScene(parent),
    width(w),
    height(h),
    cellSize(cellSize)
{
    setSceneRect(0,0,w*cellSize,h*cellSize);

}

void NetScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->setPen(QPen(QColor(255, 140, 0, 125)));

    QPointF topLeft = sceneRect().topLeft();
    QPointF bottomRight = sceneRect().bottomRight();
    double startX= topLeft.x();
    double startY = topLeft.y();

    for(double i = startX;i<=bottomRight.x();i+=cellSize) {
        painter->drawLine(QPointF(i,startY),QPointF(i,bottomRight.y()));
    }
    for(double j = startY;j<=bottomRight.y();j+=cellSize) {
        painter->drawLine(QPointF(startX,j),QPointF(bottomRight.x(),j));
    }
}
int NetScene::getHeight() const
{
    return height;
}

void NetScene::setHeight(int value)
{
    height = value;
}

int NetScene::getWidth() const
{
    return width;
}

void NetScene::setWidth(int value)
{
    width = value;
}

int NetScene::getCellSize() const
{
    return cellSize;
}

void NetScene::setCellSize(int value)
{
    cellSize = value;
}

