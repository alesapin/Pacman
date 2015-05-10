#ifndef FIELD_H
#define FIELD_H
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include "netscene.h"
#include "ui/resourceloader.h"
#include <QPoint>
#include <vector>
#include <QMouseEvent>
enum CellType{
    WALL,FOOD,CAPSULE,GHOST,PACMAN,EMPTY
};

class Field : public QGraphicsView
{
public:
    Field(int w,int h,int cs);
    CellType getCurrentMode() const;
    void setCurrentMode(const CellType &value);
    void toFile(QString fileName);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    int width;
    int height;
    int cellSize;
    CellType currentMode;
    std::vector<std::vector<CellType>> data;
    std::vector<std::vector<QGraphicsItem*>> items;
    void removeItem(int i,int j);
    void drawWall(int i,int j);
    void drawEmpty(int i,int j);
    void drawPacman(int i,int j);
    void drawFood(int i,int j);
    void drawGhost(int i,int j);
    void drawCapsule(int i,int j);
    void drawCell(int i,int j,CellType type);
    void drawRandomPacman();
    QPoint getPacmanPos();
    bool hasEmpty();
    int countGhosts();
    void removeRandomGhost();
    void drawBorder();
    QString dataToString();
    void stringToFile(QString name,QString data);
    QChar converToSym(CellType t);
};

#endif // FIELD_H
