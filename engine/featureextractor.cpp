#include "featureextractor.h"
#include <QDebug>

std::map<std::string, double> FeatureExtractor::getFeatures(GameState &state, Direction action)
{
    std::vector<std::vector<bool>> food = state.getFood();
    std::vector<std::vector<bool>> walls = state.getLayout()->getWalls();
    std::vector<QPointF> ghosts;
    std::vector<AgentState> ghostsStates;
    for(std::size_t i = 1;i<state.getAgentStates().size();++i){
        ghosts.push_back(state.getAgentPosition(i));
        ghostsStates.push_back(state.getAgentState(i));
    }
    std::map<std::string,double> features;
    features["bias"] = 1.0;
    double x = state.getPacmanPosition().x();
    double y = state.getPacmanPosition().y();
    QPointF vect=Actions::directionToVector(action);
    double dx =vect.x();
    double dy =vect.y();
    int nextx = (int)(x+dx);
    int nexty = (int)(y+dy);
    QPointF nextPos = QPointF(nextx,nexty);
    for(AgentState& ghost:ghostsStates){
        if(ghost.getScarryTimer()==0){
            std::vector<QPointF> nbrs = Actions::getLegalNeighbours(ghost.getPosition(),walls);
            if(std::find(nbrs.begin(),nbrs.end(),nextPos)!=nbrs.end()){
                features["close-ghosts"]+=1;
            }
            double dist = Util::distToGhost(nextPos,state,ghost.getPosition());
            features["ghost-dist"]+= dist/(walls.size()*walls[0].size());
        }
    }
    double sumOfTimers = 0;
    for(int i =0;i<ghostsStates.size();++i){
        if(ghostsStates[i].getScarryTimer() > 0 ) sumOfTimers+=1;
    }
    if(sumOfTimers >= 0){
        std::vector<QPointF> capsules = state.getCapsules();
        if(std::find(capsules.begin(),capsules.end(),nextPos) != capsules.end()){
            features["eat-capsule"] = 1.0;
        }
        double dist = Util::closestCapsule(nextPos,state);
        if(dist >=0){
            features["close-capsule"] = dist/(walls.size()*walls[0].size());
        }
    }
    if(features["close-ghosts"]==0 && food[nextx][nexty]){
        features["eat-food"] = 1.0;
    }

    double dist = closestFood(nextPos,food,walls);
    if(dist>=0){
        features["closest-food"] = dist/(walls.size()*walls[0].size());
    }
    for(auto iter=features.begin();iter!=features.end();++iter){
        iter->second/=10.0;
    }
    return features;
}

double FeatureExtractor::closestFood(QPointF currentPosition, const std::vector<std::vector<bool> > &food, const std::vector<std::vector<bool> > &walls)
{
    std::deque<std::tuple<QPointF,double>> fringe;
    fringe.push_back(std::make_tuple(currentPosition,0));
    std::set<QPointF,PointComparator> expanded;
    while(!fringe.empty()){
        std::tuple<QPointF,double> current = fringe.front();
        fringe.pop_front();
        QPointF pos = std::get<0>(current);
        double dist = std::get<1>(current);
        if(expanded.find(pos)!=expanded.end()){
            continue;
        }
        expanded.insert(pos);
        if(food[pos.x()][pos.y()]){
            return dist;
        }
        std::vector<QPointF> nbrs = Actions::getLegalNeighbours(pos,walls);
        for(QPointF nbr:nbrs){
            fringe.push_back(std::make_tuple(nbr,dist+1));
        }
    }
    return -1;
}
