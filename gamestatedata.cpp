#include "gamestatedata.h"
#include <QDebug>
GameStateData::GameStateData(GameStateData *prev)
{
    if(prev != 0){
        food = std::vector< std::vector<bool> >(prev->food);
        capsules = std::vector<QPointF>(prev->capsules);
        agentStates = std::vector<AgentState>(prev->agentStates);
        layout = Layout(prev->layout);
        eaten = std::vector<QPointF>(prev->eaten);
        score = prev->score;
    }
    lose = false;
    win = false;
    scoreChange = 0;
}

GameStateData::GameStateData(Layout &lay)
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
    scoreChange = 0;
    layout = Layout(lay);
}

bool GameStateData::operator==(const GameStateData &other)
{
    if(agentStates.size()!=other.agentStates.size()) return false;
    for (int i =0;i<agentStates.size();++i){
        if(agentStates[i]!=other.agentStates[i]) return false;
    }
    if(food.size()!=other.food.size() || food[0].size()!=other.food[0].size()) return false;
    for (int i =0;i<food.size();++i){
        for (int j =0;j<food[0].size();++j){
            if(food[i][j]!=other.food[i][j]) return false;
        }
    }
    if(capsules.size()!=other.capsules.size()) return false;
    for(int i =0;i<capsules.size();++i){
        if(capsules[i]!=other.capsules[i]) return false;
    }
    if(score!=other.score) return false;
    return true;
}

void GameStateData::intitialize(Layout* lay, int numAgents)
{
    food = std::vector< std::vector<bool> >(lay->getFood());
    capsules = std::vector <QPointF> (lay->getCapsules());
    layout= Layout(*lay);
    score = 0;
    scoreChange = 0;
    agentStates = std::vector<AgentState> ();
    QPointF pacmanPoint = lay->getPacmanPosition();
    agentStates.push_back(AgentState(Configuration(pacmanPoint,STOP),true));
    for (int i = 0; i<lay->getAgentsPositions().size();++i){
        QPointF agentPoint = lay->getAgentsPositions()[i];
        agentStates.push_back(AgentState(Configuration(agentPoint,STOP),false));
    }
}

GameStateData::GameStateData( GameStateData &other)
{
    food = std::vector< std::vector<bool> >(other.food);
    capsules = std::vector<QPointF>(other.capsules);
    agentStates = std::vector<AgentState>(other.agentStates);
    layout = Layout(other.layout);
    eaten = std::vector<QPointF>(other.eaten);
    score = other.score;
    lose = other.lose;
    win = other.win;
    scoreChange = other.scoreChange;
}

AgentState& GameStateData::getPacmanState()
{

    return agentStates[0];
}

Layout& GameStateData::getLayout()
{
    return layout;
}

std::vector<std::vector<bool> > GameStateData::getFood()
{
    return food;
}

std::vector<QPointF> GameStateData::getFoodAsList()
{
    std::vector<QPointF> result;
    for (int i = 0;i<food.size();++i){
        for (int j =0;j<food[0].size();++j){
            if(food[i][j]) result.push_back(QPointF(i,j));
        }
    }
    return result;
}

void GameStateData::addScore(int num)
{
    score+=num;
}

void GameStateData::setFood(int i, int j, bool val)
{
    food[i][j]=val;
}

int GameStateData::getScore()
{
    return score;
}

int GameStateData::getNumFood()
{
    int result = 0;
    for (int i = 0;i<food.size();++i){
        for (int j =0;j<food[0].size();++j){
            if(food[i][j]) result++;
        }
    }
    return result;
}

void GameStateData::setWin()
{
    win = true;
}

void GameStateData::setLose()
{
    lose = true;
}

bool GameStateData::getWin()
{
    return win;
}

bool GameStateData::getLose()
{
    return lose;
}

