#ifndef MULTIAGENTSEARCH_H
#define MULTIAGENTSEARCH_H
#include "engine/agent.h"
#include "engine/util.h"
class MultiAgentSearch : public Agent
{
public:
    MultiAgentSearch(int depth);
    int getDepth() const;
    void setDepth(int value);
    double evaluationFunction(GameState& state);
protected:
    int depth;

};

#endif // MULTIAGENTSEARCH_H
