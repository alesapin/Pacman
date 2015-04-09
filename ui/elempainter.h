#ifndef ELEM_PAINTER_H
#define ELEM_PAINTER_H
#include <QPainter>
enum ElemType{
    FIRST,SECOND,THIRD,FOURTH,LEFT,RIGHT,UP,DOWN,FULL,LEFT_CROSS,RIGHT_CROSS,UP_CROSS,DOWN_CROSS,FULL_CROSS,HORIZ,VERT,NONE
};

class ElemPainter
{
public:
    ElemPainter(double w,double h,QPainter* p);
    void drawElem(double ox,double oy,ElemType type);
    void drawFirstArc(double ox,double oy);
    void drawSecondArc(double ox,double oy);
    void drawThirdArc(double ox,double oy);
    void drawFourthArc(double ox,double oy);
    void drawLeftArc(double ox,double oy);
    void drawRightArc(double ox,double oy);
    void drawUpArc(double ox,double oy);
    void drawDownArc(double ox,double oy);
    void drawFullArc(double ox,double oy);
    void drawVertWall(double ox,double oy);
    void drawHorizWall(double ox,double oy);
    void drawUpCross(double ox,double oy);
    void drawDownCross(double ox,double oy);
    void drawLeftCross(double ox,double oy);
    void drawRightCross(double ox,double oy);
    void drawFullCross(double ox,double oy);
    void drawQuadArc(QRectF quad,double start,double end);
private:
    double width;
    double height;
    QPainter* painter;
};

#endif // ARCER_H
