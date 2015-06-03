#include "wallitem.h"
#include "elempainter.h"
#include <QDebug>
#include <QPen>
#include <QTransform>
#include <QRectF>
/**
 * @brief WallPainter::WallPainter
 * @param parent
 * @param w
 * @param cs
 * @param c
 * @param pw
 */
WallItem::WallItem(std::vector<std::vector<bool> > w, double cs, QColor c, double pw):
    walls(w),
    cellSize(cs),
    color(c),
    penWidth(pw)
{
    setCacheMode(QGraphicsItem::ItemCoordinateCache);
    if (pw == -1) {
        penWidth = cellSize / 26;
    }
    for(std::size_t i=0;i<w.size();++i){
        std::reverse(w[i].begin(),w[i].end());
    }
    walls = std::vector<std::vector<bool>>(w);
}

WallItem::~WallItem()
{
}

QRectF WallItem::boundingRect() const
{
    return QRectF(0,0,walls[0].size()*cellSize,walls.size()*cellSize);
}

void WallItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(color,penWidth,Qt::SolidLine,Qt::FlatCap,Qt::RoundJoin));

//
    painter->translate((walls[0].size())*cellSize,0);
    painter->rotate(90);
    ElemPainter* elemPainter = new ElemPainter(cellSize,cellSize,painter);

    for (std::size_t i = 0;i<walls.size();++i){
        for (std::size_t j=0;j<walls[0].size();++j){
            elemPainter->drawElem(i*cellSize,j*cellSize,checkCell(i,j));
        }
    }
    delete elemPainter;
}


ElemType WallItem::checkCell(int i,int j)
{
    if (!walls[i][j]) return NONE;
    int up = j-1;
    int down = j+1;
    int left = i-1;
    int right = i+1;
    bool leftCell = false;
    bool rightCell = false;
    bool upCell = false;
    bool downCell = false;
    bool luCell = false;//walls[i-1][j-1];
    bool ruCell = false;//walls[i+1][j-1];
    bool ldCell =false; //walls[i-1][j+1];
    bool rdCell = false;//walls[i+1][j+1];
    int width = walls.size();
    int height = walls[0].size();
    if(up >= 0){
        upCell = walls[i][up];
        if(left >= 0){
            luCell = walls[i-1][j-1];
        }
        if(right < width){
            ruCell = walls[i+1][j-1];
        }
    }
    if(down < height){
        downCell = walls[i][down];
        if(left >= 0){
            ldCell = walls[i-1][j+1];
        }
        if(right < width){
            rdCell = walls[i+1][j+1];
        }
    }
    if(left >= 0){
        leftCell = walls[left][j];
    }
    if(right < width){
        rightCell = walls[right][j];
    }

    int crossSum = leftCell+rightCell+upCell+downCell;

    if(crossSum == 4){
        int sum = luCell+ruCell+ldCell+rdCell;
        if (sum == 4){
            return NONE;//NONE
        }else if (sum == 1 || (sum == 2 && (  (luCell && rdCell) || (ldCell && ruCell)))){
            return FULL_CROSS;
        }else if (sum == 2){
            if (luCell && ruCell) return DOWN_CROSS;
            if (ldCell && rdCell) return UP_CROSS;
            if (luCell && ldCell) return RIGHT_CROSS;
            if (ruCell && rdCell) return LEFT_CROSS;
        }else if (sum == 3){
            if (!ldCell) return FIRST;
            if (!rdCell) return SECOND;
            if (!luCell) return FOURTH;
            if (!ruCell) return THIRD;
        }
    }
    if (crossSum == 0){
        return FULL;
    }else if (crossSum == 1){
        if(upCell) return UP;
        if(downCell) return DOWN;
        if(leftCell) return LEFT;
        if(rightCell) return RIGHT;
    }else if (crossSum == 2){
        if (upCell && downCell) return VERT;
        if (leftCell && rightCell) return HORIZ;
        if (upCell && leftCell) return FOURTH;
        if (upCell && rightCell) return THIRD;
        if (downCell && leftCell) return FIRST;
        if (downCell && rightCell) return SECOND;
    } else if (crossSum == 3){

        if(!leftCell){
            if(!ruCell || !rdCell){
                return RIGHT_CROSS;
            }
            return VERT;
        }
        if(!rightCell){
            if(!luCell || !ldCell){
                return LEFT_CROSS;
            }
            return VERT;
        }
        if(!upCell){
            if(!rdCell || ! ldCell){
                return DOWN_CROSS;
            }
            return HORIZ;
        }
        if(!downCell){
           if(!luCell || !ruCell){
                return UP_CROSS;
           }
           return HORIZ;
        }
    }
    return NONE;
}
