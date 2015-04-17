#include "pacmanlearningagent.h"
#include <QDebug>


PacmanLearningAgent::PacmanLearningAgent(GameState& startState,int numTrain, double eps, double alp, double gam):
    LearningAgent(numTrain,eps,alp,gam)
{
    index = 0;
}

double PacmanLearningAgent::getQValue(GameState &state, Direction action)
{
    return qValues[std::make_tuple(state,action)];
}

Direction PacmanLearningAgent::getAction(GameState &state)
{

    std::vector<Direction> legalActions = state.getLegalPacmanActions();
    Direction action = NOACTION;
    if(Util::tossCoin(epsilon)){
        int index = rand() % legalActions.size();
        action =  legalActions[index];
    }else{
        action =  computeActionFromQValues(state);
    }
    doAction(state,action);
    return action;
}

void PacmanLearningAgent::update(GameState &state, Direction action, GameState &nextState, double reward)
{
    std::vector<Direction> legalActions = nextState.getLegalPacmanActions();
    std::vector<double> qvals;
    std::tuple<GameState,Direction> key = std::make_tuple(state,action);
    for(Direction act:legalActions){
        qvals.push_back(getQValue(nextState,act));
    }
    double qVal = getQValue(state,action);
    if(qvals.size() > 0){
        double value = *std::max_element(qvals.begin(),qvals.end());
        qValues[key] =  (1 - alpha) * qVal + alpha*(reward + discount*value);
    }else{
        qValues[key] =   (1 - alpha)*qVal + alpha*reward;
    }
}

double PacmanLearningAgent::computeValueFromQValues(GameState &state)
{
    std::vector<Direction> legalActions = state.getLegalPacmanActions(); // упразднить
    if(legalActions.empty()){
        return 0;
    }
    std::vector<double> currentValues;
    for(Direction dir:legalActions){
        currentValues.push_back(getQValue(state,dir));
    }
    return *std::max_element(currentValues.begin(),currentValues.end());
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

void PacmanLearningAgent::final(GameState &finalState)
{
    double deltaReward = finalState.getScore() - lastState.getScore();

    observeOneAction(lastState,lastAction,finalState,deltaReward);
    sumOfTrainRewards += finalState.getScore();

    qDebug() <<"Прошло:" <<episodesPast;
    endEpisode();

    //qDebug() << qValues.size();
    if (episodesPast == numTraining){
        qDebug() << "Обучено! ";
    }
}
