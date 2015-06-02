#ifndef CLYDEGHOSTAGENT_H
#define CLYDEGHOSTAGENT_H
#include "directionalghostagent.h"
class ClydeGhostAgent:public DirectionalGhostAgent
{
public:
    ClydeGhostAgent(int index);
private:
    QPointF countTarget(const GameState &state);
};

#endif // CLYDEGHOSTAGENT_H
