#include "directionalghostagent.h"
#include <QDebug>
DirectionalGhostAgent::DirectionalGhostAgent(int index):
    GhostAgent(index)
{
}
const int DirectionalGhostAgent::BLINKY_NUMBER = 1;
const int DirectionalGhostAgent::PINKY_NUMBER = 2;
const int DirectionalGhostAgent::INKY_NUMBER = 3;
const int DirectionalGhostAgent::CLYDE_NUMBER = 4;
std::map<Direction, double> DirectionalGhostAgent::getDistribution(GameState &state)
{
    std::map<Direction,double> result;
    if(state.getAgentState(index).getScarryTimer()==0){
        Direction toPacman = Util::ghostWayToPoint(index,countTarget(state),state);
        result[toPacman]=1.0;
    }else{
        std::vector<Direction> legalActions = GhostRules::getLegalActions(state,index);
        result[legalActions[rand() % legalActions.size()]] = 1.0;
    }
    return result;
}

void DirectionalGhostAgent::changeMode()
{
    if(mode == CHASE){
        mode = SCATTER;
    }else{
        mode = CHASE;
    }
}

void DirectionalGhostAgent::setMode(GhostBehavior b)
{
    mode = b;
}

GhostBehavior DirectionalGhostAgent::getMode()
{
    return mode;
}

QPointF DirectionalGhostAgent::countTarget(const GameState &state)
{
    return state.getPacmanPosition();
}

