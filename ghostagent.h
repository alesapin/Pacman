#ifndef GHOSTAGENT_H
#define GHOSTAGENT_H
#include "agent.h"
#include "gamestate.h"
#include <map>
class GhostAgent: public Agent
{
public:
    GhostAgent(int ind);
    int getIndex();
    Direction getAction(GameState& state);
    virtual std::map<Direction,double> getDistribution(GameState& state) = 0;
};

#endif // GHOSTAGENT_H
