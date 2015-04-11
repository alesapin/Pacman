#include "randomghostagent.h"
#include <QDebug>



RandomGhostAgent::RandomGhostAgent(int ind):
    GhostAgent(ind)
{

}


std::map<Direction, double> RandomGhostAgent::getDistribution(GameState &state)
{
    std::map<Direction,double> result;
    for(auto act: state.getLegalAction(index)){
        result[act] = 1.;
    }
    return result;
}