#ifndef AGENT_H
#define AGENT_H
#include "gamestate.h"
#include "configuration.h"
class Agent
{
public:
     virtual Direction getAction(GameState& state) = 0;
protected:
    int index;
};

#endif // AGENT_H
