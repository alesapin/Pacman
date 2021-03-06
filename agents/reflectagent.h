#ifndef REFLECTAGENT_H
#define REFLECTAGENT_H
#include "agent.h"
#include <cmath>
#include "engine/util.h"
class ReflectAgent:public Agent
{
public:
    ReflectAgent();
    Direction getAction(GameState& state);
    double evaluationFunction(GameState& currentGameState,Direction dir);
};

#endif // REFLECTAGENT_H
