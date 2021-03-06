#include "pacmanrules.h"
#include <QDebug>

const double PacmanRules::PACMAN_SPEED = 1.0;
std::vector<Direction> PacmanRules::getLegalActions(const GameState& state)
{
    AgentState pacmanState = state.getPacmanState();
    Configuration pacConf= pacmanState.getConfiguration();
    return Actions::getPossibleActions(pacConf,state.getLayout()->getWalls());
}

void PacmanRules::applyAction(GameState& state, Direction dir)
{
    std::vector<Direction> legal = PacmanRules::getLegalActions(state);
    if(legal.size()==1 && legal[0]!=STOP){
        dir = legal[0];
    }else if (legal.size() > 1 && std::find(legal.begin(),legal.end(),dir) == legal.end()){
        Direction pacmanDir = state.getPacmanState().getDireciton();
        bool sflag = false;
        bool nflag = false;
        bool wflag = false;
        bool eflag = false;
        for(std::size_t i =0;i<legal.size()-1;++i){
            switch(legal[i]){
            case SOUTH:
                sflag = true;
                break;
            case NORTH:
                nflag = true;
                break;
            case EAST:
                eflag = true;
                break;
            case WEST:
                wflag = true;
                break;
            default:
                break;
            }
        }
        if((eflag && wflag) || (sflag && nflag)){
            if(std::find(legal.begin(),legal.end(),pacmanDir) != legal.end()){
                dir = pacmanDir;
            }else{
                dir = STOP;
            }
        }else{
            dir = STOP;
        }
    }
    AgentState pacmanState = state.getPacmanState();
    QPointF vect = Actions::directionToVector(dir,PacmanRules::PACMAN_SPEED);
    pacmanState.setConfiguration(pacmanState.getConfiguration().generateSuccessor(vect));
    state.setPacmanState(pacmanState);
    QPointF next = pacmanState.getPosition();
    int nearestX = (int)(next.x()+0.5);
    int nearestY = (int)(next.y()+0.5);
    QPointF nearest(nearestX,nearestY);
    if (Util::manhattanDistance(next,nearest) <= 0.5){
        PacmanRules::consume(nearest,state);
    }
}

void PacmanRules::consume(QPointF pos, GameState& state)
{
    double x =pos.x();
    double y = pos.y();
    if(state.hasFood(x,y)){
        state.addScore(10);

        state.setFood(x,y,false);
        state.setEatenFood(QPointF(x,y));
        int numFood = state.getNumFood();
        if (numFood == 0 && !state.isLose()){
            state.addScore(500);
            state.setWin();

        }
    }
    std::vector<QPointF> capsules = state.getCapsules();
    if(std::find(capsules.begin(),capsules.end(),pos)!=capsules.end()){
        state.setEatenCapsule(pos);
        state.removeCapsule(pos);
        state.scaryGhosts(GhostRules::SCARED_TIME);
    }
}
