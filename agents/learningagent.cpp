#include "learningagent.h"



LearningAgent::LearningAgent(int numTrain, double eps, double alp, double gam):
    episodesPast(0),
    sumOfTrainRewards(0),
    sumOfTestRewards(0),
    numTraining(numTrain),
    epsilon(eps),
    alpha(alp),
    discount(gam)
{

}

bool LearningAgent::isTraining()
{
    return episodesPast < numTraining;
}

bool LearningAgent::isTesting()
{
    return !isTraining();
}

void LearningAgent::startEpisode()
{
    lastAction = NOACTION;
    lastState = 0;
    episodeRewards = 0;
}

void LearningAgent::endEpisode()
{
    if(episodesPast < numTraining){
        sumOfTrainRewards += episodeRewards;
    } else{
        sumOfTestRewards += episodeRewards;
    }
    episodesPast++;
    if( episodesPast > numTraining){
        epsilon = 0;
        alpha = 0;
    }
}

void LearningAgent::doAction(GameState &state, Direction dir)
{
    lastState = &state;
    lastAction = dir;
}

void LearningAgent::observeOneAction(GameState &state, Direction action, GameState &nextState, double deltaReward)
{
    episodeRewards += deltaReward;
    update(state,action,nextState,deltaReward);
}

std::vector<Direction> LearningAgent::getLegalAction(GameState &state)
{
    return state.getLegalPacmanActions();
}

GameState *LearningAgent::observationFuction(GameState &state)
{
    if(lastState){
        double reward = state.getScore() - lastState->getScore();
        observeOneAction(*lastState,lastAction,state,reward);
    }
    return &state;
}