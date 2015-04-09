#ifndef UTIL_H
#define UTIL_H
#include <QPoint>
#include <vector>
class Util
{
public:
    static double manhattanDistance(QPointF f,QPointF s);
    static int maxIndex(std::vector<double> vect);
};

#endif // UTIL_H
