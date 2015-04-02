#include "pacmanrules.h"
#include "util.cpp"
#include <QDebug>

const double PacmanRules::PACMAN_SPEED = 1.0;
std::vector<Direction> PacmanRules::getLegalActions(GameState& state)
{
    AgentState pacmanState = state.getPacmanState();
    Configuration pacConf= pacmanState.getConfiguration();
    Layout pacLay = state.getData().getLayout();
    return Actions::getPossibleActions(pacConf,pacLay.getWalls());
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
        for(auto i =0;i<legal.size()-1;++i){
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
    AgentState* pacmanState = &state.getPacmanState();
    QPointF vect = Actions::directionToVector(dir,PacmanRules::PACMAN_SPEED);
    pacmanState->setConfiguration(pacmanState->getConfiguration().generateSuccessor(vect));

    QPointF next = pacmanState->getPosition();
    int nearestX = (int)(next.x()+0.5);
    int nearestY = (int)(next.y()+0.5);
    QPointF nearest(nearestX,nearestY);
    if (manhattanDistance(next,nearest) <= 0.5){
        PacmanRules::consume(nearest,state);
    }
}

void PacmanRules::consume(QPointF pos, GameState& state)
{
    double x =pos.x();
    double y = pos.y();
    if(state.getData().getFood()[x][y]){
        state.getData().addScore(10);
        state.getData().setFood(x,y,false);
        state.setEatenFood(QPointF(x,y));
        int numFood = state.getNumFood();
        if (numFood == 0 && !state.getData().getLose()){
            state.getData().addScore(500);
            state.getData().setWin();
        }
    }
    std::vector<QPointF> capsules = state.getCapsules();
    if(std::find(capsules.begin(),capsules.end(),pos)!=capsules.end()){
        state.setEatenCapsule(pos);
        state.removeCapsule(pos);
        state.scaryGhosts(GhostRules::SCARED_TIME);
    }
}
