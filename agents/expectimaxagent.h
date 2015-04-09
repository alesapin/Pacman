#ifndef EXPECTIMAXAGENT_H
#define EXPECTIMAXAGENT_H
#include "multiagentsearch.h"
#include "engine/configuration.h"
#include <limits>
class ExpectimaxAgent :public MultiAgentSearch
{
public:
    ExpectimaxAgent(int d):MultiAgentSearch(d){}
    Direction getAction(GameState& state);
private:
    double expectimax(GameState& state,int dpth,int agentIndex);
    double maxVal(GameState& state,int dpth,int agentIndex);
    double expectVal(GameState& state,int dpth,int agentIndex);
};

#endif // EXPECTIMAXAGENT_H
