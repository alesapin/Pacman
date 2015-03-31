#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "gamestatedata.h"
class GameState
{
public:
    GameState(GameState* prevstate=0);
    GameState( GameState&);
    GameState( Layout& lay);
    std::vector<Direction> getLegalAction(int agentNum);
    GameState* generateSuccessor(int agentIndex,Direction dir);
    QPointF getPacmanPosition();
    std::vector<Direction> getLegalPacmanAction();
    GameState& generatePacmanSuccessor(Direction dir);
    int getScore();
    void setGhostState(int index,AgentState state);
    AgentState& getPacmanState();
    GameStateData& getData();
    AgentState &getGhostState(int index);
    std::vector<AgentState> getAgentStates();
    QPointF getEaten();
    QPointF setEaten(QPointF);
    int getNumFood();
    std::vector<std::vector<bool> > getFood();
    std::vector<QPointF> getFoodAsList();
    std::vector<std::vector<bool> > getWalls();
    void setLose();
    bool hasFood(int x,int y);
    bool hasWall(int x,int y);
    bool isLose();
    bool isWin();
    std::vector<QPointF> getCapsules();
    void addScore(int i);
private:
    GameStateData data;
    QPointF eaten;

};

#endif // GAMESTATE_H
