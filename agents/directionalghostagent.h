#ifndef PAIRGHOSTAGENT_H
#define PAIRGHOSTAGENT_H
#include "ghostagent.h"
#include "engine/ghostrules.h"
#include "engine/util.h"
enum GhostBehavior{
    SCATTER,CHASE
};

class DirectionalGhostAgent: public  GhostAgent
{
public:
    static const int BLINKY_NUMBER;
    static const int PINKY_NUMBER;
    static const int INKY_NUMBER;
    static const int CLYDE_NUMBER;
    DirectionalGhostAgent(int index);
    std::map<Direction,double> getDistribution(GameState &state);
    void changeMode();
    void setMode(GhostBehavior b);
    GhostBehavior getMode();
protected:
    virtual QPointF countTarget(const GameState& state);
    GhostBehavior mode;
};

#endif // PAIRGHOSTAGENT_H
