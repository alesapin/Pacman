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
    GameState(const GameState&);
    GameState( Layout& lay);
    ~GameState();
    bool operator==(const GameState& other) const;
    bool operator<(const GameState& other) const;
    //Action methods
    std::vector<Direction> getLegalActions(int agentNum) const;
    GameState* generateSuccessor(int agentIndex,Direction dir);
    std::vector<Direction> getLegalPacmanActions() const;
    GameState* generatePacmanSuccessor(Direction dir);

    //service methods
    void removeCapsule(QPointF pos);
    void scaryGhosts(int time);
    bool isScared(int num);
    bool hasFood(int x,int y);
    bool hasWall(int x,int y);
    void addScore(int i);

    //Getters and Setters

    QPointF getPacmanPosition()const ;
    AgentState getPacmanState() const;
    void setPacmanState(AgentState state);
    void setAgentState(int index,AgentState state);
    AgentState getAgentState(int index) const;
    QPointF getAgentPosition(int index) const;
    int getScore() const;
    int getNumFood() const;
    std::vector<QPointF> getFoodAsList() const;
    const std::vector<std::vector<bool> > &getFood() const;
    void setFood(int x,int y,bool val);
    void setWin();
    bool isLose() const;
    bool isWin() const;
    void setLose();
    QPointF getEatenFood() const;
    void setEatenFood(QPointF);
    QPointF getEatenCapsule() const;
    void setEatenCapsule(QPointF);
    const Layout &getLayout() const;
    std::vector<QPointF> getCapsules() const;
    std::vector<AgentState> getAgentStates() const;


private:

     struct GameData{
        GameData(Layout&);
        GameData(const GameData&);
        GameData();
        Layout* layout;
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
