#include "ghostrules.h"
#include <QDebug>
extern double manhattanDistance(QPointF,QPointF);


const double GhostRules::COLLISION_TOLERANCE= 0.7;
const double GhostRules::GHOST_SPEED = 1.0;
const double GhostRules::SCARED_TIME = 40;

std::vector<Direction> GhostRules::getLegalActions(GameState &state, int ghostIndex)
{
        Configuration conf = state.getGhostState(ghostIndex).getConfiguration();
        Layout lay = state.getData().getLayout();
        std::vector<Direction> legal = Actions::getPossibleActions(conf,lay.getWalls());
        Direction reverse = Actions::reverseDirection(conf.getDirection());
        auto stopPosition = std::find(legal.begin(),legal.end(),STOP);
        if ( stopPosition != legal.end() ) {
            legal.erase(stopPosition);
        }
        auto reversePosition = std::find(legal.begin(),legal.end(),reverse);
        if (reversePosition != legal.end() && legal.size() > 1) {
            legal.erase(reversePosition);
        }
        return legal;
}

void GhostRules::applyAction(GameState &state, Direction dir, int ghostIndex)
{
    std::vector<Direction> legal = GhostRules::getLegalActions(state,ghostIndex);
    if(std::find(legal.begin(),legal.end(),dir)==legal.end()){
        qDebug() << "Illegal ghost Direction";
        throw 2;
    }
    AgentState ghostState = state.getGhostState(ghostIndex);
    double speed = GhostRules::GHOST_SPEED;
    if (ghostState.getScarryTimer()){
        speed /= 2.0;
    }
    QPointF vect = Actions::directionToVector(dir,speed);
    ghostState.setConfiguration(ghostState.getConfiguration().generateSuccessor(vect));
    state.setGhostState(ghostIndex,ghostState);
}

void GhostRules::decrementTimer(AgentState& ghostState)
{
    int timer = ghostState.getScarryTimer();
    if (timer == 1){
        //Пока не совсем ясно зачем;
    }
    ghostState.setScarryTimer(std::max(0,timer-1));
}

void GhostRules::checkDeath(GameState &state, int agentIndex)
{
    QPointF pacmanPos = state.getPacmanPosition();
    if(agentIndex==0){
        std::vector<AgentState> agentStates = state.getAgentStates();
        for(int i = 1;i < agentStates.size();++i){
            AgentState ghostState = agentStates[i];
            QPointF ghostPosition = ghostState.getConfiguration().getPosition();
            if(GhostRules::canKill(ghostPosition,pacmanPos)){
                GhostRules::collide(state,ghostState,i);
            }
        }
    }else{
        AgentState ghostState = state.getGhostState(agentIndex);
        QPointF ghostPosition = ghostState.getConfiguration().getPosition();
        if(GhostRules::canKill(pacmanPos,ghostPosition)){
            GhostRules::collide(state,ghostState,agentIndex);
        }
    }
}

void GhostRules::collide(GameState &state, AgentState &ghostState, int agentIndex)
{
    if(ghostState.getScarryTimer() >0){
        state.addScore(200);
        GhostRules::placeGhost(state,ghostState);
        ghostState.setScarryTimer(0);
    } else{
        if(!state.getData().getWin()){
            state.addScore(-500);
            state.setLose();
        }
    }
}

bool GhostRules::canKill(QPointF pacmanPosition, QPointF ghostPosition)
{
    return manhattanDistance(ghostPosition,pacmanPosition) <= GhostRules::COLLISION_TOLERANCE;
}

void GhostRules::placeGhost(GameState &state, AgentState& ghostState)
{
    ghostState.setConfiguration(ghostState.getStartConfiguration());
}



