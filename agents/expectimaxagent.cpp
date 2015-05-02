#include "expectimaxagent.h"


Direction ExpectimaxAgent::getAction(GameState &state)
{

    return std::get<0>(expectimax(state,0,0));
}

std::tuple<Direction,double> ExpectimaxAgent::expectimax(GameState &state, int dpth, int agentIndex)
{
    if (dpth == depth || state.isLose() || state.isWin()) {
        return std::make_tuple (NOACTION,evaluationFunction(state));
    }
    if (agentIndex == 0) {
        return maxVal(state,dpth,agentIndex);
    } else {
        return expectVal(state,dpth,agentIndex);
    }
}

std::tuple<Direction,double> ExpectimaxAgent::maxVal(GameState &state, int dpth, int agentIndex)
{
    std::tuple<Direction,double> v  =   std::make_tuple(NOACTION,-std::numeric_limits<double>::infinity());
    std::vector<Direction> availableActions = state.getLegalActions(agentIndex);
    int nextAgent = (agentIndex+1)%state.getAgentStates().size();
    if (nextAgent == 0){
        dpth+=1;
    }
    for(auto action:availableActions){
        GameState* nextState = state.generateSuccessor(agentIndex,action);
        std::tuple<Direction,double> innerResult = expectimax(*nextState,dpth,nextAgent);
        delete nextState;
        if(std::get<1>(innerResult) > std::get<1>(v)){
            v = std::make_tuple(action,std::get<1>(innerResult));
        }
    }
    return v;
}

std::tuple<Direction,double> ExpectimaxAgent::expectVal(GameState &state, int dpth, int agentIndex)
{
    std::tuple<Direction,double> v  =   std::make_tuple(NOACTION,0);
    std::vector<Direction> availableActions = state.getLegalActions(agentIndex);
    int nextAgent = (agentIndex+1)%state.getAgentStates().size();
    if (nextAgent == 0){
        dpth+=1;
    }
    double prob = 1.0/ availableActions.size();
    for(auto action : availableActions){
        GameState* nextState = state.generateSuccessor(agentIndex,action);
        std::tuple<Direction,double> innerResult = expectimax(*nextState,dpth,nextAgent);
        delete nextState;
        std::get<1>(v) += prob * std::get<1>(innerResult);
    }
    return v;
}
