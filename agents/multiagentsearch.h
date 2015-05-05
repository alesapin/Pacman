#ifndef MULTIAGENTSEARCH_H
#define MULTIAGENTSEARCH_H
#include "agent.h"
#include "engine/util.h"
class MultiAgentSearch : public Agent
{
public:
    MultiAgentSearch(int depth);
protected:
    int depth;
    double evaluationFunction(GameState& state);

};

#endif // MULTIAGENTSEARCH_H
