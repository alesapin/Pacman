#include "pacmanlearningagent.h"
#include <QDebug>


PacmanLearningAgent::PacmanLearningAgent(int numTrain, double eps, double alp, double gam):
    LearningAgent(numTrain,eps,alp,gam)
{
    index = 0;
    difference = 0;
}

double PacmanLearningAgent::getQValue(GameState &state, Direction action)
{
    double qVal = 0;
    std::map<std::string,double> feature = FeatureExtractor::getFeatures(state,action);
    for(auto iter=feature.begin();iter!=feature.end();++iter){

        qVal += weights[iter->first]*iter->second;
    }
    return qVal;
}


Direction PacmanLearningAgent::getAction(GameState &state)
{
    GameState&  currentState = *(this->observationFuction(state));
    std::vector<Direction> legalActions = currentState.getLegalPacmanActions();
    Direction action = NOACTION;
    if(Util::tossCoin(epsilon)){
        int index = rand() % legalActions.size();
        action =  legalActions[index];
    }else{
        action =  computeActionFromQValues(currentState);
    }
    doAction(currentState,action);
    return action;
}

void PacmanLearningAgent::update(GameState &state, Direction action, GameState &nextState, double reward)
{

    std::map<std::string,double> feature = FeatureExtractor::getFeatures(state,action);
    std::vector<double> qVals;
    for(Direction act:nextState.getLegalPacmanActions()){
        qVals.push_back(getQValue(nextState,act));
    }
    if(qVals.empty()){
        qVals.push_back(0);
    }
    double maxVal = *std::max_element(qVals.begin(),qVals.end());
    difference =  reward+ discount*maxVal - getQValue(state,action);
    for(auto iter=feature.begin();iter!=feature.end();++iter){
        weights[iter->first] += alpha*difference*iter->second;
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
