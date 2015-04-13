#include "pacmanlearningagent.h"



PacmanLearningAgent::PacmanLearningAgent(int numTrain, double eps, double alp, double gam):
    LearningAgent(numTrain,eps,alp,gam)
{

}

double PacmanLearningAgent::getQValue(GameState &state, Direction action)
{
    std::tuple<GameState*,Direction> key = std::make_tuple(&state,action);

    if(qValues.find(key)==qValues.end()){
        return 0;
     }
    return qValues[key];
}

Direction PacmanLearningAgent::getAction(GameState &state)
{
    std::vector<Direction> legalActions = state.getLegalPacmanActions();
    if(Util::tossCoin(epsilon)){
        int index = rand() % legalActions.size();
        return legalActions[index];
    }else{
        return computeActionFromQValues(state);
    }
}

void PacmanLearningAgent::update(GameState &state, Direction action, GameState &nextState, double reward)
{
    std::vector<Direction> legalActions = nextState.getLegalPacmanActions();
    std::vector<double> qvals;
    std::tuple<GameState*,Direction> key = std::make_tuple(&state,action);

    for(Direction act:legalActions){
        qvals.push_back(qValues[std::make_tuple(&nextState,act)]);
        if(qvals.size() > 0){
            qValues[key] =  (1 - alpha) * qValues[key] + alpha*(reward + discount*(* std::max(qvals.begin(),qvals.end())));
        }else{
            qValues[key] =  (1 - alpha) * qValues[key] + alpha*(reward);
        }
    }
}

double PacmanLearningAgent::computeValueFromQValues(GameState &state)
{
    std::vector<Direction> legalActions = getLegalAction(state); // упразднить
    if(legalActions.empty()){
        return 0;
    }
    std::vector<double> currentValues;
    for(Direction dir:legalActions){
        currentValues.push_back(getQValue(state,dir));
    }
    return *std::max(currentValues.begin(),currentValues.end());
}

Direction PacmanLearningAgent::computeActionFromQValues(GameState &state)
{
    std::vector<Direction> legalActions = state.getLegalPacmanActions();
    if(legalActions.empty()){
        return NOACTION;
    }
    Direction maxAction = NOACTION;
    double maxVal = -std::numeric_limits<double>::infinity();
    for(Direction act:legalActions){
        double currentVal = getQValue(state,act);
        if(currentVal > maxVal){
            maxVal = currentVal;
            maxAction = act;
        }
    }
    return maxAction;
}

double PacmanLearningAgent::getValue(GameState &state)
{
    return computeValueFromQValues(state);
}

Direction PacmanLearningAgent::getPolicyAction(GameState &state)
{
    return computeActionFromQValues(state);
}
