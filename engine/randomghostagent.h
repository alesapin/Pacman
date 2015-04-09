#ifndef RANDOMGHOSTAGENT_H
#define RANDOMGHOSTAGENT_H
#include "ghostagent.h"
class RandomGhostAgent: public GhostAgent
{
public:
    RandomGhostAgent(int ind);
    std::map<Direction,double> getDistribution(GameState &state);
};

#endif // RANDOMGHOSTAGENT_H
