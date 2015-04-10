#include "multiagentsearch.h"
#include <QDebug>
MultiAgentSearch::MultiAgentSearch(int depth)
{
    this->depth = depth;
    index = 0;
}

int MultiAgentSearch::getDepth() const
{
    return depth;
}

void MultiAgentSearch::setDepth(int value)
{
    depth = value;
}

double MultiAgentSearch::evaluationFunction(GameState &state)
{
    QPointF currentPacmanPos = state.getPacmanPosition();
    std::vector<QPointF> newFood = state.getFoodAsList();
    std::vector<AgentState> ghostStates = state.getAgentStates();
    double score =  state.getScore();
    if (newFood.size() > 0) {
        double dist = std::numeric_limits<double>::infinity();
        for (QPointF pos : newFood) {
            dist = std::min(dist,Util::manhattanDistance(pos,currentPacmanPos));
        }
        if(dist == 1.0){
            score += 1;
        }else{
            score -= dist;
        }
    }
    double ghostDist = Util::manhattanDistance(currentPacmanPos,state.getGhostState(1).getPosition());
    for(int i =2 ;i<ghostStates.size();++i){
        ghostDist = std::min(ghostDist,Util::manhattanDistance(currentPacmanPos,state.getGhostState(i).getPosition()));

    }
    std::vector<QPointF> capsules = state.getCapsules();
    if(std::find(capsules.begin(),capsules.end(),currentPacmanPos)!=capsules.end()){
        score += 200;
    }
    if(ghostDist <= 1){
        score -= 1000;
    }else{
        score += ghostDist;
    }
    if(state.isWin()){
        score += 10000;
    }
    qDebug() << "scr:" << score;
    return score;
}

