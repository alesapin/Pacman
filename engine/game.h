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
#include "gameoptions.h"
class Game
{
public:
    static const std::string LEARNING;
    static const std::string MINIMAX;
    static const std::string EPECTIMAX;
    static const std::string RUSH;
    static const std::string RANDOM;



    GameState *step();
    Layout *getLayout();
    ~Game();
    void restartGame();
    bool isLearning();
    void trainAgent();
    static Game *parseOptions(GameOptions&);
 private:
    GameState* currentGameState;
    GameState* startState;
    int currentMover;
    Layout* layout;
    PacmanLearningAgent* pacman;
    std::vector<Agent*> agents;
    Game(std::vector<Agent*> agents,Layout* lay,bool learn);
    bool learn;

};

#endif // GAME_H
