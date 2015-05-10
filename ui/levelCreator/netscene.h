#ifndef NETSCENE_H
#define NETSCENE_H
#include <QGraphicsScene>
#include <QPainter>
#include <QObject>
#include <QRectF>
#include <QPen>
#include <QColor>
class NetScene : public QGraphicsScene
{
public:
    NetScene(int w,int h,int cellSize,QObject* parent=0);
protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
private:
    int width;
    int height;
    int cellSize;
};

#endif // NETSCENE_H
