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

GameState::GameState(const GameState &o)
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

std::vector<Direction> GameState::getLegalActions(int agentNum) const
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
    QPointF agentPos = this->getAgentPosition(agentIndex);
    //qDebug()<<"(" << agentPos.x() <<"," << agentPos.y() << ")";
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

QPointF GameState::getPacmanPosition() const
{
    return data.agentStates[0].getPosition();
}

std::vector<Direction> GameState::getLegalPacmanActions() const
{
    return getLegalActions(0);
}

GameState* GameState::generatePacmanSuccessor(Direction dir)
{
    return generateSuccessor(0,dir);
}

int GameState::getScore() const
{
    return data.score;
}

void GameState::setAgentState(int index, AgentState state)
{
    data.agentStates[index] = state;
}

AgentState GameState::getPacmanState() const
{
    return data.agentStates[0];
}

AgentState GameState::getAgentState(int index) const
{
    //TODO: Призраки тоже должны быть с 0, пока норм
    return data.agentStates[index];
}

QPointF GameState::getAgentPosition(int index) const
{
    return data.agentStates[index].getPosition();
}

std::vector<AgentState> GameState::getAgentStates() const
{
    return data.agentStates;
}

QPointF GameState::getEatenFood() const
{
    return data.eatenFood;
}

void GameState::setEatenFood(QPointF e)
{
    data.eatenFood = e;
}

QPointF GameState::getEatenCapsule() const
{
    return data.eatenCapsule;
}

void GameState::setEatenCapsule(QPointF caps)
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

int GameState::getNumFood() const
{
    int result = 0;
    for (std::size_t i = 0;i<data.food.size();++i){
        for (std::size_t j =0;j<data.food[0].size();++j){
            if(data.food[i][j]) result++;
        }
    }
    return result;
}


std::vector<QPointF> GameState::getFoodAsList() const
{
    std::vector<QPointF> result;
    for (std::size_t i = 0;i<data.food.size();++i){
        for (std::size_t j =0;j<data.food[0].size();++j){
            if(data.food[i][j]) result.push_back(QPointF(i,j));
        }
    }
    return result;
}

const std::vector<std::vector<bool> > &GameState::getFood() const
{
    return data.food;
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

bool GameState::isLose() const
{
    return data.lose;
}

bool GameState::isWin() const
{
    return data.win;
}

const Layout& GameState::getLayout() const
{
    return *data.layout;
}

std::vector<QPointF> GameState::getCapsules() const
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

bool GameState::operator==(const GameState &other)const
{
    if(data.score!=other.data.score) return false;
    if(data.food.size()!=other.data.food.size()) return false;
    if(data.food[0].size()!=other.data.food[0].size()) return false;
    for(int i = 0;i<data.food.size();++i){
        for(int j =0;j<data.food[0].size();++j){
            if(data.food[i][j]!=other.data.food[i][j]) return false;
        }
    }
    if(data.agentStates.size()!=other.data.agentStates.size()) return false;
    for(int i =0;i<data.agentStates.size();++i){
        AgentState our = data.agentStates[i];
        AgentState their = other.data.agentStates[i];
        if(our.getPosition()!= their.getPosition()) return false;
        if(our.getDireciton()!=their.getDireciton()) return false;
    }
    if(data.capsules.size()!=other.data.capsules.size()) return false;
    for(int i=0;i<data.capsules.size();++i){
        if(data.capsules[i]!=other.data.capsules[i])return false;
    }
    return true;
}

bool GameState::operator<(const GameState &other) const
{
    if(getScore() < other.getScore()) return true;
    if(getNumFood() < other.getNumFood()) return true;
    return false;
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
    for (int i =1;i<positions.size();++i){
        QPointF currentAgent = positions[i];
        Configuration agentConf(currentAgent,STOP);
        agentStates.push_back(AgentState(agentConf,false));
    }
    score =0;
    lose = false;
    win = false;
    layout =&lay;
}

GameState::GameData::GameData(const GameState::GameData &other)
{

    food = std::vector< std::vector<bool> >(other.food);
    capsules = std::vector<QPointF>(other.capsules);
    agentStates = std::vector<AgentState>(other.agentStates);
    layout = other.layout;
    eaten = std::vector<QPointF>(other.eaten);
    score = other.score;
    lose = other.lose;
    win = other.win;
}

GameState::GameData::GameData()
{

}
