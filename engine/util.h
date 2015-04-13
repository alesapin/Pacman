#ifndef UTIL_H
#define UTIL_H
#include <QPoint>
#include <vector>
#include <map>
#include "configuration.h"
#include <cstdlib>


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
};

#endif // UTIL_H
