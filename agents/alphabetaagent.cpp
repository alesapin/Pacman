#include "alphabetaagent.h"
#include <QDebug>
Direction AlphaBetaAgent::getAction(GameState &state)
{
    QPointF pos = state.getPacmanPosition();
    if(std::floor(pos.x()) != pos.x() || std::floor(pos.y())!= pos.y()){
        return state.getPacmanState().getDireciton();
    }
    double alpha = -std::numeric_limits<double>::infinity();
    double beta = std::numeric_limits<double>::infinity();
    std::tuple<Direction,double> result = minimax(state,0,0,alpha,beta);
//    qDebug()<< "В результате:";
//    qDebug() << std::get<0>(result);
//    qDebug() << std::get<1>(result);
    return std::get<0>(result);
}

std::tuple<Direction, double> AlphaBetaAgent::minimax(GameState &state, int dpth, int agentNum, double alpha, double beta)
{
    if(dpth == depth || state.isWin() || state.isLose()){
        return std::make_tuple (STOP,evaluationFunction(state));
    }
    if(agentNum == 0){
        return maxVal(state,dpth,agentNum,alpha,beta);
    }else{
        return minVal(state,dpth,agentNum,alpha,beta);
    }
}

std::tuple<Direction, double> AlphaBetaAgent::maxVal(GameState &state, int dpth, int agentNum, double alpha, double beta)
{
    std::tuple<Direction,double> v  =   std::make_tuple(STOP,-std::numeric_limits<double>::infinity());
    std::vector<Direction> availableActions = state.getLegalActions(agentNum);
    if( availableActions.size() == 0 ){
        std::get<1>(v) = evaluationFunction(state);
        return v;
    }
    int nextAgent = (agentNum+1)%state.getAgentStates().size();
    if(nextAgent == 0){
        dpth+=1;
    }
    for(Direction action:availableActions){
        GameState* nextState = state.generateSuccessor(agentNum,action);
        std::tuple<Direction,double> innerResult = minimax(*nextState,dpth,nextAgent,alpha,beta);
        delete nextState;
        if(std::get<1>(innerResult) > std::get<1>(v)){
            v = std::make_tuple(action,std::get<1>(innerResult));
        }
        if(std::get<1>(v) > beta){
            return v;
        }
        alpha = std::max(alpha,std::get<1>(v));
    }
    return v;
}

std::tuple<Direction, double> AlphaBetaAgent::minVal(GameState &state, int dpth, int agentNum, double alpha, double beta)
{
    std::tuple<Direction,double> v  =   std::make_tuple(STOP,std::numeric_limits<double>::infinity());
    std::vector<Direction> availableActions = state.getLegalActions(agentNum);
    if( availableActions.size() == 0 ){
        std::get<1>(v) = evaluationFunction(state);
        return v;
    }
    int nextAgent = (agentNum+1)%state.getAgentStates().size();
    if(nextAgent == 0){
        dpth+=1;
    }
    for(Direction action:availableActions){
        GameState* nextState = state.generateSuccessor(agentNum,action);
        std::tuple<Direction,double> innerResult = minimax(*nextState,dpth,nextAgent,alpha,beta);
        delete nextState;
        if(std::get<1>(innerResult) < std::get<1>(v)){
            v = std::make_tuple(action,std::get<1>(innerResult));
        }
        if(std::get<1>(v) < alpha){
            return v;
        }
        beta = std::min(beta,std::get<1>(v));
    }
    return v;
}


