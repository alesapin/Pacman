#ifndef AGENT_H
#define AGENT_H
#include "gamestate.h"
#include "configuration.h"
class Agent
{
public:
     Direction getAction(GameState state);
protected:
    int index;
};

#endif // AGENT_H
