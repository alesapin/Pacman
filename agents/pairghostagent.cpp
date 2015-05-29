#include "pairghostagent.h"
#include <QDebug>
PairGhostAgent::PairGhostAgent(int index):
    GhostAgent(index)
{
}

std::map<Direction, double> PairGhostAgent::getDistribution(GameState &state)
{
    std::map<Direction,double> result;
    if(state.getAgentState(index).getScarryTimer()==0){
        Direction toPacman = wayToPacman(state);
        qDebug() << toPacman;
        result[toPacman]=1.0;
    }else{
        result[GhostRules::getLegalActions(state,index)[0]] = 1.0;
    }
    return result;
}

Direction PairGhostAgent::wayToPacman(GameState &state)
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
    return NOACTION;
}
