#include "gamestate.h"
#include "pacmanrules.h"
#include <QDebug>

GameState::GameState(GameState *prevstate)
{
    if(prevstate!=0){
        data = GameStateData(prevstate->data);
    } else{
        data = GameStateData();
     }
    eaten = QPointF(-1,-1);
}

GameState::GameState( GameState &o)
{
    data = GameStateData(o.getData());
    eaten = QPointF(-1,-1);

}

GameState::GameState( Layout &lay)
{
    data = GameStateData();
    data.intitialize(&lay,1);
    eaten = QPointF(-1,-1);

}

std::vector<Direction> GameState::getLegalAction(int agentNum)
{
    if (isWin() || isLose()) return std::vector<Direction>();
    if(agentNum == 0){
        return PacmanRules::getLegalActions(*this);
    } else {
        //TODO: GHOSTS
        return std::vector<Direction> ();
    }
}

GameState* GameState::generateSuccessor(int agentIndex, Direction dir)
{
    if(isWin() || isLose()) qDebug()<< "Terminal state,lose/win(gamestate.cpp - 20)";
    GameState* state=new GameState(*this);
    if(agentIndex == 0){
        PacmanRules::applyAction(*state,dir);
    }
    if(agentIndex == 0){
        state->getData().addScore(-1);
    }
    return state;
}

QPointF GameState::getPacmanPosition()
{
    return data.getPacmanState().getPosition();
}

std::vector<Direction> GameState::getLegalPacmanAction()
{
    return getLegalAction(0);
}

GameState& GameState::generatePacmanSuccessor(Direction dir)
{
    return *generateSuccessor(0,dir);
}

int GameState::getScore()
{
    return data.getScore();
}

AgentState& GameState::getPacmanState()
{
    return data.getPacmanState();
}

GameStateData& GameState::getData()
{
    return data;
}

QPointF GameState::getEaten()
{
    return eaten;
}

QPointF GameState::setEaten(QPointF e)
{
    eaten = e;
}

int GameState::getNumFood()
{
    return data.getNumFood();
}

std::vector<QPointF> GameState::getFoodAsList()
{
    return data.getFoodAsList();
}

bool GameState::isLose()
{
    return data.getLose();
}

bool GameState::isWin()
{
    return data.getWin();
}
