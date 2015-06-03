#include "gamestate.h"
#include "pacmanrules.h"
#include "ghostrules.h"

#include <QDebug>


GameState::GameState()
{
    layout = 0;
    lose = false;
    win = false;
}

GameState::GameState(const GameState &other)
{

    food = other.food;
    capsules = other.capsules;
    agentStates = other.agentStates;
    layout = other.layout;
    eaten = other.eaten;
    score = other.score;
    lose = other.lose;
    win = other.win;
    eatenFood = other.eatenFood;
    eatenCapsule = other.eatenCapsule;

}

GameState::GameState(const Layout *lay)
{
    food = lay->getFood();
    capsules = lay->getCapsules();
    agentStates = std::vector<AgentState>();
    QPointF pacman = lay->getPacmanPosition();
    Configuration pacmanConf(pacman,STOP);
    agentStates.push_back(AgentState(pacmanConf,true));
    std::vector<QPointF> positions  = lay->getAgentsPositions();
    for (std::size_t i =1;i<positions.size();++i){
        QPointF currentAgent = positions[i];
        Configuration agentConf(currentAgent,STOP);
        agentStates.push_back(AgentState(agentConf,false));
    }
    score =0;
    lose = false;
    win = false;
    layout = lay;
    eatenFood = QPointF(-1,-1);
    eatenCapsule = QPointF(-1,-1);
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
    if(isWin() || isLose()) qDebug() << "Terminal state,lose/win";
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
    return agentStates[0].getPosition();
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
    return score;
}

void GameState::setAgentState(int index, AgentState state)
{
    agentStates[index] = state;
}

AgentState GameState::getPacmanState() const
{
    return agentStates[0];
}

AgentState GameState::getAgentState(int index) const
{
    //TODO: Призраки тоже должны быть с 0, пока норм
    return agentStates[index];
}

QPointF GameState::getAgentPosition(int index) const
{
    return agentStates[index].getPosition();
}

std::vector<AgentState> GameState::getAgentStates() const
{
    return agentStates;
}

int GameState::getSquare() const
{
    return layout->getWalls()[0].size()*layout->getWalls().size();
}

QPointF GameState::getEatenFood() const
{
    return eatenFood;
}

void GameState::setEatenFood(QPointF e)
{
    eatenFood = e;
}

QPointF GameState::getEatenCapsule() const
{
    return eatenCapsule;
}

void GameState::setEatenCapsule(QPointF caps)
{
    eatenCapsule = caps;
}

void GameState::removeCapsule(QPointF pos)
{
    auto remPos = std::find(capsules.begin(),capsules.end(),pos);
    capsules.erase(remPos);
}

void GameState::scaryGhosts(int time)
{
    for(std::size_t i = 1;i<agentStates.size();++i){
        agentStates[i].setScarryTimer(time);
    }
}

bool GameState::isScared(int num)
{
    AgentState ghost = agentStates[num];
    return ghost.getScarryTimer() > 0;
}

bool GameState::hasFood(int x, int y)
{
    return food[x][y];
}

int GameState::getNumFood() const
{
    int result = 0;
    for (std::size_t i = 0;i<food.size();++i){
        for (std::size_t j =0;j<food[0].size();++j){
            if(food[i][j]) result++;
        }
    }
    return result;
}


std::vector<QPointF> GameState::getFoodAsList() const
{
    std::vector<QPointF> result;
    for (std::size_t i = 0;i<food.size();++i){
        for (std::size_t j =0;j<food[0].size();++j){
            if(food[i][j]) result.push_back(QPointF(i,j));
        }
    }
    return result;
}

const std::vector<std::vector<bool> > &GameState::getFood() const
{
    return food;
}

void GameState::setLose()
{
    lose = true;
}

void GameState::setFood(int x, int y, bool val)
{
    food[x][y] = val;
}

void GameState::setWin()
{
    win = true;
}

bool GameState::isLose() const
{
    return lose;
}

bool GameState::isWin() const
{
    return win;
}

const Layout *GameState::getLayout() const
{
    return layout;
}

std::vector<QPointF> GameState::getCapsules() const
{
    return capsules;
}

void GameState::addScore(int i)
{
    score += i;
}

GameState::~GameState()
{
   // delete layout;
}

bool GameState::operator==(const GameState &other)const
{
    if(score!=other.score) return false;
    if(food.size()!=other.food.size()) return false;
    if(food[0].size()!=other.food[0].size()) return false;
    for(std::size_t i = 0;i<food.size();++i){
        for(std::size_t j =0;j<food[0].size();++j){
            if(food[i][j]!=other.food[i][j]) return false;
        }
    }
    if(agentStates.size()!=other.agentStates.size()) return false;
    for(std::size_t i =0;i<agentStates.size();++i){
        AgentState our = agentStates[i];
        AgentState their = other.agentStates[i];
        if(our.getPosition()!= their.getPosition()) return false;
        if(our.getDireciton()!=their.getDireciton()) return false;
    }
    if(capsules.size()!=other.capsules.size()) return false;
    for(std::size_t i=0;i<capsules.size();++i){
        if(capsules[i]!=other.capsules[i])return false;
    }
    return true;
}

bool GameState::operator<(const GameState &other) const
{
    if(getScore() < other.getScore()) return true;
    if(getNumFood() < other.getNumFood()) return true;
    return false;
}

GameState &GameState::operator=(const GameState &other)
{
    food = other.food;
    capsules = other.capsules;
    agentStates = other.agentStates;
    layout = other.layout;
    eaten = other.eaten;
    score = other.score;
    lose = other.lose;
    win = other.win;
    eatenFood = other.eatenFood;
    eatenCapsule = other.eatenCapsule;
    return *this;
}

void GameState::setPacmanState(AgentState state)
{
    agentStates[0] = state;
}





