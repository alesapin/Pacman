#ifndef ALPHABETAAGENT_H
#define ALPHABETAAGENT_H
#include "multiagentsearch.h"
#include "engine/util.h"
#include "engine/configuration.h"
#include <tuple>
#include <limits>

class AlphaBetaAgent : public MultiAgentSearch
{
public:
    AlphaBetaAgent(int d) : MultiAgentSearch(d){}
    Direction getAction(GameState &state);
    std::tuple<Direction,double> minimax(GameState& state,int dpth,int agentNum,double alpha,double beta);
    std::tuple<Direction,double> maxVal(GameState& state,int dpth,int agentNum,double alpha,double beta);
    std::tuple<Direction,double> minVal(GameState& state,int dpth,int agentNum,double alpha,double beta);
};

#endif // ALPHABETAAGENT_H
