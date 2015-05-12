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

    int getCellSize() const;
    void setCellSize(int value);

    int getWidth() const;
    void setWidth(int value);

    int getHeight() const;
    void setHeight(int value);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
private:
    int width;
    int height;
    int cellSize;
};

#endif // NETSCENE_H
