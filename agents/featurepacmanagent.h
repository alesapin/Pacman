#ifndef FEATUREPACMANAGENT_H
#define FEATUREPACMANAGENT_H
#include "pacmanlearningagent.h"
#include "engine/featureextractor.h"
class FeaturePacmanAgent: public PacmanLearningAgent
{
public:
    FeaturePacmanAgent(GameState& state, int numTrain, double eps, double alp, double gam);
protected:
    double getQValue(GameState &state, Direction action);
    void update(GameState& state,Direction action,GameState& nextState,double reward);
private:
    std::map<std::string,double> weights;
    double difference;
};

#endif // FEATUREPACMANAGENT_H
