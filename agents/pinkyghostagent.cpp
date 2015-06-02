#include "pinkyghostagent.h"

PinkyGhostAgent::PinkyGhostAgent(int index):
    DirectionalGhostAgent(index)
{
}



QPointF PinkyGhostAgent::countTarget(const GameState &state)
{
    if(mode == SCATTER){
        return QPointF(1,state.getLayout()->getWalls()[0].size());
    }
    Configuration pacmanConf = state.getPacmanState().getConfiguration();
    QPointF target = pacmanConf.getPosition();

    QPointF pacmanVect;
    if(pacmanConf.getDirection() == NORTH){
        pacmanVect = QPointF(-1,-1);
    }else{
        pacmanVect = Actions::directionToVector(pacmanConf.getDirection());
    }
    std::vector<std::vector<bool>> walls = state.getLayout()->getWalls();
    int width = walls.size();
    int height = walls[0].size();
    for(int i = 0;i<4;++i){
        target.setX(target.x()+pacmanVect.x());
        target.setY(target.y()+pacmanVect.y());
    }
    if(target.x() > width - 1){
        target.setX(width-1);
    }
    if(target.x() < 0){
        target.setX(0);
    }
    if(target.y() > height - 1){
        target.setY(height-1);
    }
    if(target.y() < 0){
        target.setY(0);
    }
    return target;
}
