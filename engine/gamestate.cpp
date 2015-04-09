#include "gamestate.h"
#include "pacmanrules.h"
#include "ghostrules.h"

#include <QDebug>

GameState::GameState(GameState *prevstate)
{
    if(prevstate!=0){
        data = GameStateData(prevstate->data);
    } else{
        data = GameStateData();
     }
    eatenFood = QPointF(-1,-1);
    eatenCapsule = QPointF(-1,-1);
}

GameState::GameState( GameState &o)
{
    data = GameStateData(o.getData());
    eatenFood = QPointF(-1,-1);

}

GameState::GameState( Layout &lay)
{
    data = GameStateData();
    data.intitialize(&lay,1);
    eatenFood = QPointF(-1,-1);

}

std::vector<Direction> GameState::getLegalAction(int agentNum)
{
    if (isWin() || isLose()) return std::vector<Direction>();
    if(agentNum == 0){
        return PacmanRules::getLegalActions(*this);
    } else {
       return GhostRules::getLegalActions(*this,agentNum);
    }
}

GameState* GameState::generateSuccessor(int agentIndex, Direction dir)
{
    if(isWin() || isLose()) qDebug()<< "Terminal state,lose/win(gamestate.cpp - 20)";
    GameState* state=new GameState(*this);
    if(agentIndex == 0){
        PacmanRules::applyAction(*state,dir);
    }else{
        GhostRules::applyAction(*state,dir,agentIndex);
    }
    if(agentIndex == 0){
        state->getData().addScore(-1);
    }else{
        GhostRules::decrementTimer(state->getGhostState(agentIndex));
    }
    GhostRules::checkDeath(*state,agentIndex);
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

GameState* GameState::generatePacmanSuccessor(Direction dir)
{
    return generateSuccessor(0,dir);
}

int GameState::getScore()
{
    return data.getScore();
}

void GameState::setGhostState(int index, AgentState state)
{
    data.setAgentState(index,state);
}

AgentState& GameState::getPacmanState()
{
    return data.getPacmanState();
}

GameStateData& GameState::getData()
{
    return data;
}

AgentState &GameState::getGhostState(int index)
{
    return data.getGhostState(index);
}

std::vector<AgentState> GameState::getAgentStates()
{
    return data.getAgentStates();
}

QPointF GameState::getEatenFood()
{
    return eatenFood;
}

QPointF GameState::setEatenFood(QPointF e)
{
    eatenFood = e;
}

QPointF GameState::getEatenCapsule()
{
    return eatenCapsule;
}

QPointF GameState::setEatenCapsule(QPointF caps)
{
    eatenCapsule = caps;
}

void GameState::removeCapsule(QPointF pos)
{
    data.removeCapsule(pos);
}

void GameState::scaryGhosts(int time)
{
    data.scarryGhosts(time);
}

bool GameState::isScared(int num)
{
    AgentState ghost = data.getAgentStates()[num];
    return ghost.getScarryTimer() > 0;
}

int GameState::getNumFood()
{
    return data.getNumFood();
}

std::vector<QPointF> GameState::getFoodAsList()
{
    return data.getFoodAsList();
}

void GameState::setLose()
{
    data.setLose();
}

bool GameState::isLose()
{
    return data.getLose();
}

bool GameState::isWin()
{
    return data.getWin();
}

std::vector<QPointF> GameState::getCapsules()
{
    return data.getCapsules();
}

void GameState::addScore(int i)
{
    data.addScore(i);
}

GameState::~GameState()
{
}
