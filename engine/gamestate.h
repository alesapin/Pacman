#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <vector>
#include "agentstate.h"
#include "layout.h"
#include <QPointF>
class GameState
{
public:
    //Constructors/destructors
    GameState(GameState* prevstate=0);
    GameState( GameState&);
    GameState( Layout& lay);
    ~GameState();
    //Action methods
    std::vector<Direction> getLegalAction(int agentNum);
    GameState* generateSuccessor(int agentIndex,Direction dir);
    std::vector<Direction> getLegalPacmanAction();
    GameState* generatePacmanSuccessor(Direction dir);

    //service methods
    void removeCapsule(QPointF pos);
    void scaryGhosts(int time);
    bool isScared(int num);
    bool hasFood(int x,int y);
    bool hasWall(int x,int y);
    void addScore(int i);

    //Getters and Setters

    QPointF getPacmanPosition();
    AgentState getPacmanState();
    void setPacmanState(AgentState state);
    void setGhostState(int index,AgentState state);
    AgentState getGhostState(int index);
    int getScore();
    int getNumFood();
    std::vector<QPointF> getFoodAsList();
    void setFood(int x,int y,bool val);
    void setWin();
    bool isLose();
    bool isWin();
    void setLose();
    QPointF getEatenFood();
    QPointF setEatenFood(QPointF);
    QPointF getEatenCapsule();
    QPointF setEatenCapsule(QPointF);
    const Layout &getLayout() ;
    std::vector<QPointF> getCapsules();
    std::vector<AgentState> getAgentStates();


private:

     struct GameData{
        GameData(Layout&);
        GameData(const GameData&);
        GameData();
        Layout layout;
        std::vector< std::vector<bool> > food;
        std::vector< AgentState> agentStates;
        std::vector<QPointF> capsules;
        std::vector<QPointF> eaten;
        bool win;
        bool lose;
        int score;
        QPointF eatenFood;
        QPointF eatenCapsule;
     } data;

};

#endif // GAMESTATE_H
