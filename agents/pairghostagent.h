#ifndef PAIRGHOSTAGENT_H
#define PAIRGHOSTAGENT_H
#include "ghostagent.h"
#include "engine/ghostrules.h"
class PairGhostAgent: public  GhostAgent
{
public:
    PairGhostAgent(int index);
    std::map<Direction,double> getDistribution(GameState &state);
private:
    Direction wayToPacman(GameState& state);
};

#endif // PAIRGHOSTAGENT_H
