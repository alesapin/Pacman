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
    double startX= rect.topLeft().x();
    double startY = rect.topLeft().y();

    for(double i = startX;i<=rect.bottomRight().x();i+=cellSize) {
        painter->drawLine(QPointF(i,startY),QPointF(i,rect.bottomRight().y()));
    }
    for(double j = startY;j<=rect.bottomRight().y();j+=cellSize) {
        painter->drawLine(QPointF(startX,j),QPointF(rect.bottomRight().x(),j));
    }
}
