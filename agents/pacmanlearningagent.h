#ifndef PACMANLEARNINGAGENT_H
#define PACMANLEARNINGAGENT_H
#include "learningagent.h"
#include <map>
#include "engine/util.h"
class PacmanLearningAgent : public LearningAgent
{
public:
    PacmanLearningAgent(int numTrain, double eps, double alp, double gam);
protected:
     double getQValue(GameState &state, Direction action);
     Direction getAction(GameState &state); //После переноса рандома в util
     void update(GameState& state,Direction action,GameState& nextState,double reward);
     double computeValueFromQValues(GameState& state);
     Direction computeActionFromQValues(GameState& state);
     double getValue(GameState &state);
     Direction getPolicyAction(GameState &state);
private:
     std::map<std::tuple<GameState*,Direction>,double> qValues;
};

#endif // PACMANLEARNINGAGENT_H
