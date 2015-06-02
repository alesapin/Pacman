#ifndef PINKYGHOSTAGENT_H
#define PINKYGHOSTAGENT_H
#include "ghostagent.h"
#include "directionalghostagent.h"
class PinkyGhostAgent:public DirectionalGhostAgent
{
public:
    PinkyGhostAgent(int index);
protected:
    QPointF countTarget(const GameState& state);
};

#endif // PINKYGHOSTAGENT_H
