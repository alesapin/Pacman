#include "randomghostagent.h"
#include <QDebug>



RandomGhostAgent::RandomGhostAgent(int ind):
    GhostAgent(ind)
{

}


std::map<Direction, double> RandomGhostAgent::getDistribution(GameState &state)
{
    std::map<Direction,double> result;
    for(Direction act: state.getLegalActions(index)){
        result[act] = 1.;
    }
    Util::normalize(result);
    return result;
}
