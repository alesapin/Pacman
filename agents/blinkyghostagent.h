#ifndef BLINKYGHOSTAGENT_H
#define BLINKYGHOSTAGENT_H
#include "directionalghostagent.h"
class BlinkyGhostAgent: public DirectionalGhostAgent
{
public:
    BlinkyGhostAgent(int index);
protected:
    QPointF countTarget(const GameState &state);
};

#endif // BLINKYGHOSTAGENT_H
