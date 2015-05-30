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
#include "agents/keyboardagent.h"
#include "agents/pairghostagent.h"
#include "gameoptions.h"
#include <vector>
class GameOptions;
class Game
{
public:
    static const QString LEARNING;
    static const QString MINIMAX;
    static const QString EXPECTIMAX;
    static const QString RUSH;
    static const QString RANDOM;
    static const QString KEYBOARD;
    static const QString DIRECTIONAL;
    static Game *parseOptions(GameOptions& opts);

    GameState *step();
    Layout *getLayout();
    ~Game();
    void restartGame();
    bool isLearning();
    void trainAgent();
    void setFocus();
    void keyBoardEvent(QKeyEvent *event);
    int getCurrentIter() const;
    int getTotalIters() const;
    int trainStep();
 private:
    GameState* currentGameState;
    GameState* startState;

    int currentMover;
    Layout* layout;
    PacmanLearningAgent* pacman;
    KeyBoardAgent* keyboard;
    std::vector<Agent*> agents;
    Game(std::vector<Agent*> agents,Layout* lay,bool learn);
    bool learn;
};

#endif // GAME_H
