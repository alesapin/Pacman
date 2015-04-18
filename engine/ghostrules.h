
#ifndef GHOSTRULES_H
#define GHOSTRULES_H
#include <vector>
#include <algorithm>
#include "gamestate.h"
#include "actions.h"
#include "util.h"
class GhostRules
{
public:
    static std::vector<Direction> getLegalActions(const GameState& state,int ghostIndex);
    static void applyAction(GameState& state,Direction dir,int ghostIndex);
    static AgentState decrementTimer(AgentState ghostState);
    static void checkDeath(GameState& state,int agentIndex);
    static void collide(GameState& state,AgentState ghostState,int agentIndex);
    static bool canKill(QPointF pacmanPosition,QPointF ghostPosition);
    static void placeGhost(GameState& state,AgentState& ghostState,int ghostIndex);
    static const double GHOST_SPEED;
    static const double COLLISION_TOLERANCE;
    static const double SCARED_TIME;
};

#endif // GHOSTRULES_H
