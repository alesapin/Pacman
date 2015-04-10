#ifndef AGENT_H
#define AGENT_H
#include "engine/gamestate.h"
#include "engine/configuration.h"
class Agent
{
public:
     virtual Direction getAction(GameState& state) = 0;
protected:
    int index;
};

#endif // AGENT_H
