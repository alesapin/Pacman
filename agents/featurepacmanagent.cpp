#include "featurepacmanagent.h"
#include <QDebug>


FeaturePacmanAgent::FeaturePacmanAgent(GameState &state, int numTrain, double eps, double alp, double gam):
    PacmanLearningAgent(state,numTrain,eps,alp,gam),
    difference(0)
{

}

double FeaturePacmanAgent::getQValue(GameState &state, Direction action)
{
    double qVal = 0;
    std::map<std::string,double> feature = FeatureExtractor::getFeatures(state,action);
    for(auto iter=feature.begin();iter!=feature.end();++iter){

        qVal += weights[iter->first]*iter->second;
    }
    return qVal;
}

void FeaturePacmanAgent::update(GameState &state, Direction action, GameState &nextState, double reward)
{

    std::map<std::string,double> feature = FeatureExtractor::getFeatures(state,action);
    std::vector<double> qVals;
    for(Direction act:nextState.getLegalPacmanActions()){
        qVals.push_back(getQValue(nextState,act));
    }
    if(qVals.empty()){
        qVals.push_back(0);
    }
    double maxVal = *std::max_element(qVals.begin(),qVals.end());
    difference =  reward+ discount*maxVal - getQValue(state,action);
    //debug <<"diff:"<<difference;
    for(auto iter=feature.begin();iter!=feature.end();++iter){
        //debug <<"{" <<iter->first.c_str() <<":"<< iter->second <<"}";
        weights[iter->first] += alpha*difference*iter->second;
        //debug <<"{"<<iter->first.c_str()<<" : "<<weights[iter->first]<<"}";
    }
}
