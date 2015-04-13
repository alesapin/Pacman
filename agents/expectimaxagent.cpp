#include "expectimaxagent.h"


Direction ExpectimaxAgent::getAction(GameState &state)
{
    std::vector<Direction> legalActions = state.getLegalPacmanActions();
    std::vector<double> expectimaxValues;
    for (auto action:legalActions) {
        GameState* nextState = state.generatePacmanSuccessor(action);
        expectimaxValues.push_back(expectimax(*nextState,0,1));
        delete nextState;
    }
    return legalActions[Util::maxIndex(expectimaxValues)];
}

double ExpectimaxAgent::expectimax(GameState &state, int dpth, int agentIndex)
{
    if (dpth == depth || state.isLose() || state.isWin()) {
        return evaluationFunction(state);
    }
    if (agentIndex == 0) {
        return maxVal(state,dpth,agentIndex);
    } else {
        return expectVal(state,dpth,agentIndex);
    }
}

double ExpectimaxAgent::maxVal(GameState &state, int dpth, int agentIndex)
{
    double v = -std::numeric_limits<double>::infinity();
    std::vector<Direction> availableActions = state.getLegalActions(agentIndex);
    int nextAgent = (agentIndex+1)%state.getAgentStates().size();
    if (nextAgent == 0){
        dpth+=1;
    }
    for(auto action:availableActions){
        GameState* nextState = state.generateSuccessor(agentIndex,action);
        double innerResult = expectimax(*nextState,dpth,nextAgent);
        delete nextState;
        if(innerResult > v){
            v = innerResult;
        }
    }
    return v;
}

double ExpectimaxAgent::expectVal(GameState &state, int dpth, int agentIndex)
{
    double v = 0;
    std::vector<Direction> availableActions = state.getLegalActions(agentIndex);
    int nextAgent = (agentIndex+1)%state.getAgentStates().size();
    if (nextAgent == 0){
        dpth+=1;
    }
    double prob = 1.0/ availableActions.size();
    for(auto action : availableActions){
        GameState* nextState = state.generateSuccessor(agentIndex,action);
        double innerResult = expectimax(*nextState,dpth,nextAgent);
        delete nextState;
        v += prob * innerResult;
    }
    return v;
}
