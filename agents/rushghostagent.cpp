#include "rushghostagent.h"
#include <QDebug>
RushGhostAgent::RushGhostAgent(int ind):
    GhostAgent(ind)
{
    index = ind;
    probScaried = 0.5;
    probAtack = 0.5;
}


RushGhostAgent::RushGhostAgent(int ind, double probAtack, double probScaried):
    GhostAgent(ind)
{
    index = ind;
    this->probAtack = probAtack;
    this->probScaried = probScaried;
}

std::map<Direction, double> RushGhostAgent::getDistribution(GameState &state)
{
    AgentState ghostState = state.getAgentState(index);
    std::vector<Direction> legalActions = state.getLegalActions(index);
    QPointF position = ghostState.getPosition();
    double speed = state.isScared(index) ? 0.5:1;

    std::vector<QPointF> actionsVector;
    for (Direction action : legalActions) {
        actionsVector.push_back(Actions::directionToVector(action,speed));
    }
    std::vector<QPointF> newPositions;
    for(QPointF vect:actionsVector){
        newPositions.push_back(QPointF(position.x()+vect.x(), position.y()+vect.y()));
    }
    QPointF pacmanPosition = state.getPacmanPosition();

    std::vector<double> distancesToPacman;
     for(QPointF newPos:newPositions){
         distancesToPacman.push_back(Util::manhattanDistance(pacmanPosition,newPos));
     }
     double bestScore = 0;
     double bestProb = 0;
     if(state.isScared(index)){
        bestScore = *std::max_element(distancesToPacman.begin(),distancesToPacman.end());
        bestProb = probScaried;
     } else {
        bestScore = *std::min_element(distancesToPacman.begin(),distancesToPacman.end());
        bestProb = probAtack;
     }
     std::vector<Direction> bestActions;
     for (int i = 0; i < distancesToPacman.size() ; ++i) {
         if(distancesToPacman[i] == bestScore){
             bestActions.push_back(legalActions[i]);
         }
     }
     std::map<Direction,double> result;
     for (Direction act : legalActions) {
         result[act] = 0.0;
     }
     for (Direction best : bestActions) {
        result[best] = bestProb / bestActions.size();
     }
     for(Direction legal:legalActions){
         result[legal] += (1-bestProb) / legalActions.size();
     }
     Util::normalize(result);
     return result;
}
