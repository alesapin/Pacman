#include "agentstate.h"

AgentState::AgentState(Configuration config, bool isPacman):
    start(config),
    current(config)
{
    this->isPacman = isPacman;
}

QPointF AgentState::getPosition()
{
    return current.getPosition();
}

Direction AgentState::getDireciton()
{
    return current.getDirection();
}

Configuration& AgentState::getConfiguration()
{
    return current;
}

void AgentState::setConfiguration(Configuration conf)
{
    current = conf;
}

bool AgentState::operator==(const AgentState &other)
{
    return current == other.current && scarryTimer == other.scarryTimer;
}

bool AgentState::operator!=(const AgentState &other)
{
    return !(*this==other);
}

AgentState::AgentState(const AgentState &other):
    start(other.start),
    current(other.current)
{
    isPacman = other.isPacman;
    numCarrying = other.numCarrying;
    numReturned = other.numReturned;
    scarryTimer = other.scarryTimer;
}


