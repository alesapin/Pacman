#include <QPointF>
#include <cmath>
double manhattanDistance(QPointF f,QPointF s){
    return std::abs(f.x()-s.x())+std::abs(f.y()-s.y());
}
