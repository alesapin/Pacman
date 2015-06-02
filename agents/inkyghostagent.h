#ifndef INKYGHOSTAGENT_H
#define INKYGHOSTAGENT_H
#include "directionalghostagent.h"
class InkyGhostAgent: public DirectionalGhostAgent
{
public:
    InkyGhostAgent(int index);
private:
    QPointF countTarget(const GameState &state);
};

#endif // INKYGHOSTAGENT_H
