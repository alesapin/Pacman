#include "blinkyghostagent.h"
#include <QDebug>



BlinkyGhostAgent::BlinkyGhostAgent(int index):
    DirectionalGhostAgent(index)
{

}

QPointF BlinkyGhostAgent::countTarget(const GameState &state)
{
    if(mode == CHASE){
        return state.getPacmanPosition();
    }else{
        return QPointF(1,1);
    }
}
