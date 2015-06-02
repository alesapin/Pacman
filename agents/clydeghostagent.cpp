#include "clydeghostagent.h"

ClydeGhostAgent::ClydeGhostAgent(int index):
    DirectionalGhostAgent(index)
{
}

QPointF ClydeGhostAgent::countTarget(const GameState &state)
{
    if(mode == SCATTER){

        auto walls = state.getLayout()->getWalls();
        return QPointF(walls.size()-1,walls[0].size()-1);
    }
    if(Util::manhattanDistance(state.getPacmanPosition(),state.getAgentPosition(index)) > 9){
        return state.getPacmanPosition();
    }else{
        auto walls = state.getLayout()->getWalls();
        return QPointF(walls.size()-1,walls[0].size()-1);
    }
}
