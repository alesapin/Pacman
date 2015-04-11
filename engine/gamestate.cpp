#include "gamestate.h"
#include "pacmanrules.h"
#include "ghostrules.h"

#include <QDebug>

GameState::GameState(GameState *prevstate)
{
    if(prevstate!=0){
        data = GameData(prevstate->data);
    } else{
        data = GameData();
     }
    data.eatenFood = QPointF(-1,-1);
    data.eatenCapsule = QPointF(-1,-1);
}

GameState::GameState( GameState &o)
{
    data = GameData(o.data);
    data.eatenFood = QPointF(-1,-1);

}

GameState::GameState( Layout &lay)
{
    data = GameData(lay);
    data.eatenFood = QPointF(-1,-1);
    data.eatenCapsule = QPointF(-1,-1);
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
        state->addScore(-1);
    }else{
        state->setAgentState(agentIndex,GhostRules::decrementTimer(state->getAgentState(agentIndex)));
    }
    GhostRules::checkDeath(*state,agentIndex);
    return state;
}

QPointF GameState::getPacmanPosition()
{
    return data.agentStates[0].getPosition();
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
    return data.score;
}

void GameState::setAgentState(int index, AgentState state)
{
    data.agentStates[index] = state;
}

AgentState GameState::getPacmanState()
{
    return data.agentStates[0];
}

AgentState GameState::getAgentState(int index)
{
    //TODO: Призраки тоже должны быть с 0, пока норм
    return data.agentStates[index];
}

QPointF GameState::getAgentPosition(int index)
{
    return data.agentStates[index].getPosition();
}

std::vector<AgentState> GameState::getAgentStates()
{
    return data.agentStates;
}

QPointF GameState::getEatenFood()
{
    return data.eatenFood;
}

QPointF GameState::setEatenFood(QPointF e)
{
    data.eatenFood = e;
}

QPointF GameState::getEatenCapsule()
{
    return data.eatenCapsule;
}

QPointF GameState::setEatenCapsule(QPointF caps)
{
    data.eatenCapsule = caps;
}

void GameState::removeCapsule(QPointF pos)
{
    auto remPos = std::find(data.capsules.begin(),data.capsules.end(),pos);
    data.capsules.erase(remPos);
}

void GameState::scaryGhosts(int time)
{
    for(int i = 1;i<data.agentStates.size();++i){
        data.agentStates[i].setScarryTimer(time);
    }
}

bool GameState::isScared(int num)
{
    AgentState ghost = data.agentStates[num];
    return ghost.getScarryTimer() > 0;
}

bool GameState::hasFood(int x, int y)
{
    return data.food[x][y];
}

int GameState::getNumFood()
{
    int result = 0;
    for (std::size_t i = 0;i<data.food.size();++i){
        for (std::size_t j =0;j<data.food[0].size();++j){
            if(data.food[i][j]) result++;
        }
    }
    return result;
}


std::vector<QPointF> GameState::getFoodAsList()
{
    std::vector<QPointF> result;
    for (std::size_t i = 0;i<data.food.size();++i){
        for (std::size_t j =0;j<data.food[0].size();++j){
            if(data.food[i][j]) result.push_back(QPointF(i,j));
        }
    }
    return result;
}

void GameState::setLose()
{
    data.lose = true;
}

void GameState::setFood(int x, int y, bool val)
{
    data.food[x][y] = val;
}

void GameState::setWin()
{
    data.win = true;
}

bool GameState::isLose()
{
    return data.lose;
}

bool GameState::isWin()
{
    return data.win;
}

const Layout& GameState::getLayout()
{
    return data.layout;
}

std::vector<QPointF> GameState::getCapsules()
{
    return data.capsules;
}

void GameState::addScore(int i)
{
    data.score += i;
}

GameState::~GameState()
{
}

void GameState::setPacmanState(AgentState state)
{
    data.agentStates[0] = state;
}


GameState::GameData::GameData(Layout &lay)
{
    food = std::vector<std::vector < bool> >(lay.getFood());
    capsules = std::vector<QPointF>(lay.getCapsules());
    agentStates = std::vector<AgentState>();
    QPointF pacman = lay.getPacmanPosition();
    Configuration pacmanConf(pacman,STOP);
    agentStates.push_back(AgentState(pacmanConf,true));
    std::vector<QPointF> positions  = lay.getAgentsPositions();
    for (int i =0;i<positions.size();++i){
        QPointF currentAgent = positions[i];
        Configuration agentConf(currentAgent,STOP);
        agentStates.push_back(AgentState(agentConf,false));
    }
    score =0;
    lose = false;
    win = false;
    layout = Layout(lay);
}

GameState::GameData::GameData(const GameState::GameData &other)
{
    food = std::vector< std::vector<bool> >(other.food);
    capsules = std::vector<QPointF>(other.capsules);
    agentStates = std::vector<AgentState>(other.agentStates);
    layout = Layout(other.layout);
    eaten = std::vector<QPointF>(other.eaten);
    score = other.score;
    lose = other.lose;
    win = other.win;
}

GameState::GameData::GameData()
{

}
