#include "ghostagent.h"


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
    std::map<Direction,double> dist = getDistribution(state);
    //choose element with max value
    auto pr = std::max_element(dist.begin(), dist.end(),
          [](const std::pair<Direction, double>& p1, const std::pair<Direction, double>& p2) {
            return p1.second < p2.second; });
    std::vector<Direction> maxVector;
    for(auto iter=dist.begin();iter!=dist.end();++iter){
        if(iter->second==pr->second) maxVector.push_back(iter->first);
    }
    int index = rand() % maxVector.size();

    return maxVector[index];
}


