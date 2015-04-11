#ifndef RUSHGHOSTAGENT_H
#define RUSHGHOSTAGENT_H
#include "ghostagent.h"
#include "engine/actions.h"
#include "engine/util.h"
class RushGhostAgent: public GhostAgent
{
public:
    RushGhostAgent(int ind);
    RushGhostAgent(int ind,double probAtack,double probScaried);
    std::map<Direction,double> getDistribution(GameState &state);
private:
    int index;
    double probAtack;
    double probScaried;
};

#endif // RUSHGHOSTAGENT_H
