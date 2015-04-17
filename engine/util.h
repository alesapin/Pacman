#ifndef UTIL_H
#define UTIL_H
#include <QPoint>
#include <vector>
#include <map>
#include "configuration.h"
#include <cstdlib>

struct PointComparator {
    bool operator()(const QPointF& p1, const QPointF& p2) const {
       return  p1.x() < p2.x() ||
                          (p1.x() == p2.x() && p1.y() < p2.y());
    }
};
class Util
{
public:
    static double manhattanDistance(QPointF f,QPointF s);
    static int maxIndex(std::vector<double> vect);
    static void normalize(std::map<Direction,double>&);
    static bool tossCoin(double prob);
    static double rand();
    static std::default_random_engine generator; //move to util
    static std::uniform_real_distribution<double> distribution;
    static void setSeed();
};

#endif // UTIL_H
