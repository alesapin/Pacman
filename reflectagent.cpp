#include "reflectagent.h"
#include <QDebug>
extern double manhattanDistance(QPointF f, QPointF s);
ReflectAgent::ReflectAgent()
{
        index = 0;
}

Direction ReflectAgent::getAction(GameState &state)
{
    std::vector<Direction> legal = state.getLegalPacmanAction();
    std::vector<double> scores;
    for (Direction dir:legal){
        scores.push_back(evaluationFunction(state,dir));
    }

    int maxInd = 0;
    for(int i =1;i<scores.size();++i){
        if(scores[maxInd] < scores[i]){

            maxInd = i;
        }
    }

    return legal[maxInd];
}

double ReflectAgent::evaluationFunction(GameState &currentGameState, Direction dir)
{
    GameState next = currentGameState.generatePacmanSuccessor(dir);
    QPointF newPos = next.getPacmanPosition();
    int foodLen = next.getNumFood();
    int oldFoodLen = currentGameState.getNumFood();
    std::vector<QPointF> newFood = next.getFoodAsList();
    double minDistToFood = 110;
    if(newFood.size()>0){
        minDistToFood = manhattanDistance(newFood[0],newPos);
        for(auto p:newFood){
            minDistToFood = std::min(minDistToFood,manhattanDistance(p,newPos));
        }
        minDistToFood *= -1;
    }
    double diffFood = oldFoodLen - foodLen;
    if (diffFood == 1){
            minDistToFood = 1;
    }
    return minDistToFood;

}
