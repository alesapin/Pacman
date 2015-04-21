#include "multiagentsearch.h"
#include <QDebug>
MultiAgentSearch::MultiAgentSearch(int depth)
{
    this->depth = depth;
    index = 0;
}

int MultiAgentSearch::getDepth() const
{
    return depth;
}

void MultiAgentSearch::setDepth(int value)
{
    depth = value;
}

double MultiAgentSearch::evaluationFunction(GameState &state)
{
    return state.getScore();
}

