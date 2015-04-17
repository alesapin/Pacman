#ifndef FEATUREEXTRACTOR_H
#define FEATUREEXTRACTOR_H
#include <map>
#include<string>
#include "gamestate.h"
#include <set>
#include <deque>
#include <tuple>
#include "actions.h"
#include "util.h"
#include <cmath>
class FeatureExtractor
{
public:
    static std::map<std::string,double> getFeatures(GameState& state,Direction action);
private:
    static double closestFood(QPointF currentPosition,const std::vector<std::vector<bool>>&food,const std::vector<std::vector<bool>>&walls);
};

#endif // FEATUREEXTRACTOR_H
