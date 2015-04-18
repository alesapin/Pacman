#ifndef PACMANLEARNINGAGENT_H
#define PACMANLEARNINGAGENT_H
#include "learningagent.h"
#include <map>
#include "engine/util.h"
#include <unordered_map>
#include <utility>
#include "engine/featureextractor.h"
class PacmanLearningAgent : public LearningAgent
{
public:
    PacmanLearningAgent(int numTrain, double eps, double alp, double gam);
    Direction getAction(GameState &state); //После переноса рандома в util
    void final(GameState& finalState);

protected:
     virtual double getQValue(GameState &state, Direction action);
     virtual void update(GameState& state,Direction action,GameState& nextState,double reward);
     double computeValueFromQValues(GameState& state);
     Direction computeActionFromQValues(GameState& state);
     double getValue(GameState &state);
     Direction getPolicyAction(GameState &state);
private:
     //std::unordered_map<std::tuple<GameState,Direction>,double,key_hash,key_equal> qValues;
     std::map<std::string,double> weights;
     double difference;
};

#endif // PACMANLEARNINGAGENT_H
