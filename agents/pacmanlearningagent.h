#ifndef PACMANLEARNINGAGENT_H
#define PACMANLEARNINGAGENT_H
#include "learningagent.h"
#include <map>
#include "engine/util.h"
#include <unordered_map>
#include <utility>
#include "engine/featureextractor.h"
struct key_hash : public std::unary_function<std::tuple<GameState,Direction>, std::size_t>
{
   std::size_t operator()(const std::tuple<GameState,Direction>& k) const
   {
      GameState g = std::get<0>(k);
      int numFood = g.getNumFood();
      double agentsX=0;
      double agentsY=0;
      for(int i=0;i<g.getAgentStates().size();++i){
          QPointF position = g.getAgentPosition(i);
          agentsX+=position.x();
          agentsY += position.y();
      }
      int score = g.getScore();
      return (13*numFood+23*agentsX+29*agentsY+std::abs(score)) + std::get<1>(k);
   }
};
struct key_equal : public std::binary_function<std::tuple<GameState,Direction>, std::tuple<GameState,Direction>, bool>
{
   bool operator()(const std::tuple<GameState,Direction>& v0, const std::tuple<GameState,Direction>& v1) const
   {
      return (
               std::get<0>(v0) == std::get<0>(v1) &&
               std::get<1>(v0) == std::get<1>(v1));
   }
};

class PacmanLearningAgent : public LearningAgent
{
public:
    PacmanLearningAgent(GameState& state, int numTrain, double eps, double alp, double gam);
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
