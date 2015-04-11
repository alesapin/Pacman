#include "util.h"


double Util::manhattanDistance(QPointF f, QPointF s)
{
    return std::abs(f.x()-s.x())+std::abs(f.y()-s.y());
}

int Util::maxIndex(std::vector<double> vect)
{
    if(vect.empty()){
        return -1;
    }
    int maxIndex = 0;
    int maxVal = vect[0];
    for(int i=1;i<vect.size();++i){
        if(vect[i] > maxVal){
            maxVal = vect[i];
            maxIndex = i;
        }
    }
    return maxIndex;
}

void Util::normalize(std::map<Direction, double> &dict)
{
    double sum = 0;
    for(auto it = dict.begin();it!=dict.end();++it){
        sum+= it->second;
    }
    for(auto it=dict.begin();it != dict.end();++it){
        dict[it->first] = it->second / sum;
    }
}
