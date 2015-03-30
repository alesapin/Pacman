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
    AgentState& getPacmanState();
    GameStateData& getData();
    QPointF getEaten();
    QPointF setEaten(QPointF);
    int getNumFood();
    std::vector<std::vector<bool> > getFood();
    std::vector<QPointF> getFoodAsList();
    std::vector<std::vector<bool> > getWalls();
    bool hasFood(int x,int y);
    bool hasWall(int x,int y);
    bool isLose();
    bool isWin();

private:
    GameStateData data;
    QPointF eaten;

};

#endif // GAMESTATE_H
