#ifndef GAMESTATEDATA_H
#define GAMESTATEDATA_H
#include <vector>
#include "agentstate.h"
#include "layout.h"
#include <QPointF>
class GameStateData
{
public:
    GameStateData(GameStateData* prev = 0);
    GameStateData( Layout& lay);
    bool operator==(const GameStateData& other);
    void intitialize(Layout* lay,int numAgents);
    GameStateData( GameStateData& other);
    AgentState& getPacmanState();
    AgentState& getGhostState(int index);
    Layout& getLayout();
    std::vector< std::vector<bool> > getFood();
    std::vector< QPointF> getFoodAsList();
    std::vector< QPointF> getCapsules();
    std::vector<AgentState> getAgentStates();
    void scarryGhosts(int time);
    void removeCapsule(QPointF capsPos);
    void addScore(int num);
    void setFood(int i,int j,bool val);
    int getScore();
    int getNumFood();
    void setWin();
    void setLose();
    bool getWin();
    bool getLose();
    void setAgentState(int intex,AgentState state);
    ~GameStateData();
private:
    std::vector< std::vector<bool> > food;
    Layout layout;
    std::vector <AgentState> agentStates;
    int score;
    std::vector<QPointF> capsules;
    std::vector<QPointF> eaten;
    bool win;
    bool lose;
    int scoreChange;
};

#endif // GAMESTATEDATA_H
