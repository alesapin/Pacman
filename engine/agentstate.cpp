#include "agentstate.h"

AgentState::AgentState(Configuration config, bool isPacman):
    start(config),
    current(config)
{
    this->isPacman = isPacman;
}

QPointF AgentState::getPosition() const
{
    return current.getPosition();
}

Direction AgentState::getDireciton() const
{
    return current.getDirection();
}

void AgentState::setPosition(QPointF pos)
{
    current.setPosition(pos);
}

Configuration AgentState::getConfiguration() const
{
    return current;
}

void AgentState::setConfiguration(Configuration conf)
{
    current = Configuration(conf);

}

int AgentState::getScarryTimer() const
{
    return scarryTimer;
}

void AgentState::setScarryTimer(int time)
{
    scarryTimer = time;
}

Configuration AgentState::getStartConfiguration() const
{
    return start;
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
    scarryTimer = other.scarryTimer;
}


