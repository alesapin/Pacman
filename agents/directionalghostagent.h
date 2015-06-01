#ifndef PAIRGHOSTAGENT_H
#define PAIRGHOSTAGENT_H
#include "ghostagent.h"
#include "engine/ghostrules.h"
class DirectionalGhostAgent: public  GhostAgent
{
public:
    DirectionalGhostAgent(int index);
    std::map<Direction,double> getDistribution(GameState &state);
private:
    Direction wayToPacman(GameState& state);
};

#endif // PAIRGHOSTAGENT_H
