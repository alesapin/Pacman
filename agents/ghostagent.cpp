#include "ghostagent.h"
#include <QDebug>

GhostAgent::GhostAgent(int ind)
{
    index = ind;
}

int GhostAgent::getIndex()
{
    return index;
}

Direction GhostAgent::getAction(GameState &state)
{
    QPointF agentPosition = state.getAgentPosition(index);
    if(std::floor(agentPosition.x())!= agentPosition.x() || std::floor(agentPosition.y() != agentPosition.y())){
        return state.getAgentState(index).getDireciton();
    }
    //TODO выбор не максимального элемента
    std::map<Direction,double> dist = getDistribution(state);
    std::vector<std::pair<Direction,double> >listRepr;
    std::copy(dist.begin(),dist.end(),std::back_inserter(listRepr));

    std::sort(listRepr.begin(),listRepr.end(),PairComparator());

    double choice = Util::rand();
    int i =0;
    double total = listRepr[i].second;
    while(total < choice){
        total += listRepr[++i].second;
    }
    return listRepr[i].first;
}


