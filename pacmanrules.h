#ifndef PACMANRULES_H
#define PACMANRULES_H
#include <vector>
#include <algorithm>
#include "gamestate.h"
#include "actions.h"

class PacmanRules
{
public:
    static std::vector<Direction> getLegalActions(GameState& state);
    static void applyAction(GameState& state,Direction dir);
    static void consume(QPointF pos,GameState& state);

private:
    static const double PACMAN_SPEED;
};

#endif // PACMANRULES_H