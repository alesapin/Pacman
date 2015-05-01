#ifndef LEARNINGAGENT_H
#define LEARNINGAGENT_H
#include "agent.h"
class LearningAgent : public Agent
{
public:
    LearningAgent(int numTrain,double eps,double alp,double gam);
    bool isTraining();
    bool isTesting();
    void startEpisode();
    void endEpisode();
    void finish(GameState& state);
    Direction getAction(GameState &state) = 0;
    GameState *observationFuction(GameState& state);
    ~LearningAgent();
    int getTrainIteration();
    int getTotalNumIters();
protected:
    virtual void update(GameState& state,Direction action,GameState& nextState,double reward) = 0;
    virtual double getQValue(GameState& state,Direction action) = 0;
    virtual double getValue(GameState& state) = 0;
    virtual Direction getPolicyAction(GameState& state) = 0;
    void doAction(GameState& state,Direction dir);
    void observeOneAction(GameState& state,Direction action,GameState& nextState,double deltaReward);
    std::vector<Direction> getLegalAction(GameState& state);


   int numTraining;
   double epsilon;
   double alpha;
   double discount;
   int episodesPast;
   double sumOfTrainRewards;
   double sumOfTestRewards;
   double episodeRewards;
   Direction lastAction;
   GameState lastState;
};

#endif // LEARNINGAGENT_H
