#include "inkyghostagent.h"



InkyGhostAgent::InkyGhostAgent(int index):
    DirectionalGhostAgent(index)
{

}

QPointF InkyGhostAgent::countTarget(const GameState &state)
{
    if(mode == SCATTER){
        return QPointF(state.getLayout()->getWalls().size(),1);
    }
    Configuration pacmanConf = state.getPacmanState().getConfiguration();
    QPointF middleOfEdge = pacmanConf.getPosition();
    QPointF vectorOfMove = Actions::directionToVector(pacmanConf.getDirection());
    auto walls = state.getLayout()->getWalls();
    int width = walls.size();
    int height = walls[0].size();
    for(int i = 0; i< 2;++i){
        middleOfEdge.setX(middleOfEdge.x()+vectorOfMove.x());
        middleOfEdge.setY(middleOfEdge.y()+vectorOfMove.y());
    }
    QPointF blinkyPos = state.getAgentPosition(DirectionalGhostAgent::BLINKY_NUMBER);
    QPointF target(middleOfEdge.x()+(middleOfEdge.x()-blinkyPos.x()),middleOfEdge.y()+(middleOfEdge.y()-blinkyPos.y()));
    if(target.x() < 0){
        target.setX(0);
    }
    if(target.x() > width - 1){
        target.setX(width-1);
    }
    if(target.y() < 0 ){
        target.setY(0);
    }
    if(target.y() > height - 1){
        target.setY(height - 1);
    }
    return target;
}
