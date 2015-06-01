#include "directionalghostagent.h"
#include <QDebug>
DirectionalGhostAgent::DirectionalGhostAgent(int index):
    GhostAgent(index)
{
}

std::map<Direction, double> DirectionalGhostAgent::getDistribution(GameState &state)
{
    std::map<Direction,double> result;
    if(state.getAgentState(index).getScarryTimer()==0){
        Direction toPacman = wayToPacman(state);
        qDebug() << toPacman;
        result[toPacman]=1.0;
    }else{
        std::vector<Direction> legalActions = GhostRules::getLegalActions(state,index);
        for(int i = 0;i<legalActions.size();++i){
            //qDebug() << legalActions[i];
        }
        //qDebug() << "_______";
        result[legalActions[rand() % legalActions.size()]] = 1.0;
    }
    return result;
}

Direction DirectionalGhostAgent::wayToPacman(GameState &state)
{

    std::deque<std::tuple<Configuration,Direction>> fringe;
    fringe.push_back(std::make_tuple(state.getAgentState(index).getConfiguration(),NOACTION));
    std::set<QPointF,PointComparator> expanded;
    bool firstStep = true;
    while(!fringe.empty()){
        std::tuple<Configuration,Direction> current = fringe.front();
        fringe.pop_front();
        Configuration conf = std::get<0>(current);
        QPointF pos = conf.getPosition();
        Direction startDirection = std::get<1>(current);
        if(expanded.find(pos)!=expanded.end()){
            continue;
        }
        expanded.insert(pos);
        if(pos == state.getPacmanPosition()){
            return startDirection;
        }

        std::vector<Direction> legal = GhostRules::getLegalActions(std::get<0>(current),state.getLayout()->getWalls());
        if(firstStep){
            for(Direction dir:legal){
                Configuration succ = conf.generateSuccessor(dir);
                fringe.push_back(std::make_tuple(succ,dir));
            }
            firstStep = false;
        }else{
            for(Direction dir:legal){
                Configuration succ = conf.generateSuccessor(dir);
                fringe.push_back(std::make_tuple(succ,startDirection));
            }
        }
    }
    std::vector<Direction> legal = state.getLegalActions(index);
    return legal[rand()%legal.size()];
}
