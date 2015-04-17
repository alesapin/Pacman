#ifndef GAME_H
#define GAME_H
#include "gamestate.h"
#include "agents/agent.h"
#include "agents/ghostagent.h"
#include "agents/alphabetaagent.h"
#include "agents/rushghostagent.h"
#include "agents/expectimaxagent.h"
#include "agents/randomghostagent.h"
#include "agents/pacmanlearningagent.h"
#include <vector>

class Game
{
public:
    Game(std::string layoutPath);
    GameState *step();
    Layout *getLayout();
    ~Game();
    void restartGame();
    bool isLearning();
    void trainAgent();
 private:
    GameState* currentGameState;
    GameState* startState;
    int currentMover;
    Layout* layout;
    PacmanLearningAgent* pacman;
    std::vector<Agent*> agents;

    void setAgents();
};

#endif // GAME_H
