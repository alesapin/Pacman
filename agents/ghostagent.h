#ifndef GHOSTAGENT_H
#define GHOSTAGENT_H
#include "agent.h"
#include "engine/gamestate.h"
#include <cstdlib>
#include <map>
#include <random>
#include "engine/util.h"
struct PairComparator {
    bool operator()(const std::pair<Direction,double>& p1, const std::pair<Direction,double>& p2) const {
       return  p1.second < p2.second;
    }
};

class GhostAgent: public Agent
{
public:
    GhostAgent(int ind);
    int getIndex();
    Direction getAction(GameState& state);
    virtual std::map<Direction,double> getDistribution(GameState& state) = 0;
};

#endif // GHOSTAGENT_H
