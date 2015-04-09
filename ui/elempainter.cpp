#include "elempainter.h"
#include <QRectF>
#include <QPainter>



ElemPainter::ElemPainter(double w, double h, QPainter* p):
    width(w),height(h),painter(p)
{

}

void ElemPainter::drawElem(double ox, double oy, ElemType type)
{
    switch (type) {
    case FIRST:
        drawFirstArc(ox,oy);
        break;
    case SECOND:
        drawSecondArc(ox,oy);
        break;
    case THIRD:
        drawThirdArc(ox,oy);
        break;
    case FOURTH:
        drawFourthArc(ox,oy);
        break;
    case UP:
        drawUpArc(ox,oy);
        break;
    case DOWN:
        drawDownArc(ox,oy);
        break;
    case LEFT:
        drawLeftArc(ox,oy);
        break;
    case RIGHT:
        drawRightArc(ox,oy);
        break;
    case FULL:
        drawFullArc(ox,oy);
        break;
    case UP_CROSS:
        drawUpCross(ox,oy);
        break;
    case DOWN_CROSS:
        drawDownCross(ox,oy);
        break;
    case LEFT_CROSS:
        drawLeftCross(ox,oy);
        break;
    case RIGHT_CROSS:
        drawRightCross(ox,oy);
        break;
    case FULL_CROSS:
        drawFullCross(ox,oy);
    case HORIZ:
        drawHorizWall(ox,oy);
        break;
    case VERT:
        drawVertWall(ox,oy);
        break;
    default:
        break;
    }
}

void ElemPainter::drawFirstArc(double ox, double oy)
{
    QRectF inner1(ox,oy+2*width/3,width/3,height/3);
    painter->drawArc(inner1,0*16,91*16);
    QRectF inner2(ox+width/3,oy+height/3,width/3,height/3);
    painter->drawArc(inner2,0*16, 91*16);

    painter->drawLine(ox+2*width/3,oy+height/3+height/6,ox+2*width/3,oy+height); //vl
    painter->drawLine(ox+width/3,oy+2*height/3+height/6, ox+width/3,oy+height); //vs
    painter->drawLine(ox,oy+height/3,ox+width/3+width/6,oy+height/3); //hl
    painter->drawLine(ox,oy+2*height/3,ox+width/6,oy+2*height/3);//hs
}

void ElemPainter::drawSecondArc(double ox, double oy)
{
    QRectF inner1(ox + 2*width/3,oy+2*width/3,width/3,height/3);
    painter->drawArc(inner1,-271*16,91*16);
    QRectF inner2(ox+width/3,oy+height/3,width/3,height/3);
    painter->drawArc(inner2,-271*16,91*16);

    painter->drawLine(ox+width/3,oy+height/3+height/6,ox+width/3,oy+height); //vl
    painter->drawLine(ox+2*width/3,oy+2*height/3+height/6, ox+2*width/3,oy+height); //vs
    painter->drawLine(ox+width/3+width/6,oy+height/3,ox+width,oy+height/3); //hl
    painter->drawLine(ox+2*width/3+width/6,oy+2*height/3,ox+width,oy+2*height/3);//hs

}

void ElemPainter::drawThirdArc(double ox, double oy)
{
    QRectF inner1(ox + 2*width/3,oy,width/3,height/3);
    painter->drawArc(inner1,181*16,91*16);
    QRectF inner2(ox+width/3,oy+height/3,width/3,height/3);
    painter->drawArc(inner2,181*16,91*16);
    painter->drawLine(ox+width/3,oy,ox+width/3,oy+height/3+height/6); //vl
    painter->drawLine(ox+2*width/3,oy,ox+2*width/3,oy+height/6); //vs
    painter->drawLine(ox+2*width/3+width/6,oy+height/3,ox+width,oy+height/3); //hs
    painter->drawLine(ox+width/3+width/6,oy+2*height/3,ox+width,oy+2*height/3);//hl
}

void ElemPainter::drawFourthArc(double ox, double oy)
{
    QRectF inner1(ox,oy,width/3,height/3);
    painter->drawArc(inner1,1*16,-91*16);
    QRectF inner2(ox+width/3,oy+height/3,width/3,height/3);
    painter->drawArc(inner2,1*16,-91*16);
    painter->drawLine(ox+width/3,oy,ox+width/3,oy+height/6);
    painter->drawLine(ox+2*width/3,oy,ox+2*width/3,oy+height/3+height/6);
    painter->drawLine(ox,oy+height/3,ox+width/6,oy+height/3);
    painter->drawLine(ox,oy+2*height/3,ox+width/3+width/6,oy+2*height/3);
}

void ElemPainter::drawLeftArc(double ox, double oy)
{
    QRectF inner2(ox+width/3,oy+height/3,width/3,height/3);
    painter->drawArc(inner2,271*16,181*16);
    painter->drawLine(ox,oy+height/3,ox+width/3+width/6,oy+height/3);
    painter->drawLine(ox,oy+2*height/3,ox+width/3+width/6,oy+2*height/3);
}

void ElemPainter::drawRightArc(double ox, double oy)
{
    QRectF inner2(ox+width/3,oy+height/3,width/3,height/3);
    painter->drawArc(inner2,91*16,181*16);
    painter->drawLine(ox+width/3+width/6,oy+height/3,ox+width,oy+height/3);
    painter->drawLine(ox+width/3+width/6,oy+2*height/3,ox+width,oy+2*height/3);
}

void ElemPainter::drawUpArc(double ox, double oy)
{
    QRectF inner2(ox+width/3,oy+height/3,width/3,height/3);
    painter->drawArc(inner2,181*16,181*16);
    painter->drawLine(ox+width/3,oy,ox+width/3,oy+height/3+height/6);
    painter->drawLine(ox+2*width/3,oy,ox+2*width/3,oy+height/3+height/6);

}

void ElemPainter::drawDownArc(double ox, double oy)
{
    QRectF inner2(ox+width/3,oy+height/3,width/3,height/3);
    painter->drawArc(inner2,1*16,181*16);
    painter->drawLine(ox+width/3,oy+height/3+height/6,ox+width/3,oy+height);
    painter->drawLine(ox+2*width/3,oy+height/3+height/6,ox+2*width/3,oy+height);
}

void ElemPainter::drawFullArc(double ox, double oy)
{
    QRectF inner2(ox+width/3,oy+height/3,width/3,height/3);
    painter->drawArc(inner2,0*16,360*16);

}
void ElemPainter::drawVertWall(double ox,double oy)
{
    painter->drawLine(ox+width/3,oy,ox+width/3,oy+height);
    painter->drawLine(ox+2*width/3,oy,ox+2*width/3,oy+height);
}
void ElemPainter::drawHorizWall(double ox,double oy)
{
    painter->drawLine(ox,oy+height/3,ox+width,oy+height/3);
    painter->drawLine(ox,oy+2*height/3,ox+width,oy+2*height/3);
}

void ElemPainter::drawUpCross(double ox, double oy)
{
    QRectF leftQuad(ox,oy,width/3,height/3);
    QRectF rightQuad(ox+2*width/3,oy,width/3,height/3);
    drawQuadArc(leftQuad,271,91);
    drawQuadArc(rightQuad,181,91);
    painter->drawLine(ox,oy+2*height/3,ox+width,oy+2*height/3);
}

void ElemPainter::drawDownCross(double ox, double oy)
{
    QRectF leftQuad(ox,oy+2*width/3,width/3,height/3);
    QRectF rightQuad(ox+2*width/3,oy+2*width/3,width/3,height/3);
    drawQuadArc(leftQuad,1,91);
    drawQuadArc(rightQuad,91,91);
    painter->drawLine(ox,oy+height/3,ox+width,oy+height/3);
}

void ElemPainter::drawLeftCross(double ox, double oy)
{
    QRectF upQuad(ox,oy,width/3,height/3);
    QRectF downQuad(ox,oy+2*width/3,width/3,height/3);
    drawQuadArc(upQuad,271,91);
    drawQuadArc(downQuad,1,91);
    painter->drawLine(ox+2*width/3,oy,ox+2*width/3,oy+height);
}

void ElemPainter::drawRightCross(double ox, double oy)
{
    QRectF upQuad(ox+2*width/3,oy,width/3,height/3);
    QRectF downQuad(ox+2*width/3,oy+2*width/3,width/3,height/3);
    drawQuadArc(upQuad,181,91);
    drawQuadArc(downQuad,91,91);
    painter->drawLine(ox+width/3,oy,ox+width/3,oy+height);
}

void ElemPainter::drawFullCross(double ox, double oy)
{
    QRectF upLQuad(ox,oy,width/3,height/3);
    QRectF downLQuad(ox,oy+2*width/3,width/3,height/3);
    QRectF upRQuad(ox+2*width/3,oy,width/3,height/3);
    QRectF downRQuad(ox+2*width/3,oy+2*width/3,width/3,height/3);
    drawQuadArc(upLQuad,271,91);
    drawQuadArc(downLQuad,1,91);
    drawQuadArc(upRQuad,181,91);
    drawQuadArc(downRQuad,91,91);
}

void ElemPainter::drawQuadArc(QRectF quad, double start, double end)
{
    painter->drawArc(quad,start*16,end*16);
    QPointF origin = quad.topLeft();
    double w = quad.width() /2;
    double ox =origin.x();
    double oy = origin.y();
    int angle = (int) start;
    switch(angle){
        case 1:
            painter->drawLine(ox,oy,ox+w,oy);
            painter->drawLine(ox+2*w,oy+w,ox+2*w,oy+2*w);
            break;
        case 91:
            painter->drawLine(ox,oy+w,ox,oy+2*w);
            painter->drawLine(ox+w,oy,ox+2*w,oy);
            break;
        case 181:
            painter->drawLine(ox,oy,ox,oy+w);
            painter->drawLine(ox+w,oy+2*w,ox+2*w,oy+2*w);
            break;
        case 271:
            painter->drawLine(ox,oy+2*w,ox+w,oy+2*w);
            painter->drawLine(ox+2*w,oy,ox+2*w,oy+w);
            break;
    }
}



