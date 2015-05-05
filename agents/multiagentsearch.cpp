#include "multiagentsearch.h"
#include <QDebug>
MultiAgentSearch::MultiAgentSearch(int depth)
{
    this->depth = depth;
    index = 0;
}


double MultiAgentSearch::evaluationFunction(GameState &state)
{
    double result = 0;
    QPointF pacmanPosition = state.getPacmanPosition();
    int totalFood = state.getLayout()->getTotalFood();
    int size = (state.getLayout()->getWalls()[0].size())*(state.getLayout()->getWalls().size());
    double coef = 1.*totalFood/size;

    double distToFood = Util::closestFood(pacmanPosition,state.getFood(),state.getLayout()->getWalls());
    if(distToFood == -1){
        result += 1000;
    }else{
        result += ((1./ (distToFood+1))*10);
    }
    double minDist = std::numeric_limits<double>::infinity();
    for(int i = 1;i<state.getAgentStates().size();++i){
        QPointF ghostPosition = state.getAgentPosition(i);
        minDist = std::min(minDist,Util::manhattanDistance(pacmanPosition,ghostPosition));
    }
    if(minDist <= 1){
        result-=5000;
    }
    if(state.getNumFood() == 0){
        result +=100000;
    }else{
        result += ((1./(state.getNumFood()))*100000);
    }
    return result;
}

