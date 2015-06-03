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
#include "agents/directionalghostagent.h"
#include "agents/blinkyghostagent.h"
#include "agents/inkyghostagent.h"
#include "agents/clydeghostagent.h"
#include "agents/pinkyghostagent.h"
#include "gameoptions.h"
#include <vector>
#include <QTimer>
#include <QObject>
class GameOptions;
class Game : public QObject
{
    Q_OBJECT
public:
    static const QString LEARNING;
    static const QString MINIMAX;
    static const QString EXPECTIMAX;
    static const QString RUSH;
    static const QString RANDOM;
    static const QString KEYBOARD;
    static const QString DIRECTIONAL;
    static const QString ORIGINAL;

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
 public slots:
    void switchMode();
 private:
    GameState* currentGameState;
    GameState* startState;
    int scatterTime;
    int chaseTime;
    Layout* layout;
    PacmanLearningAgent* pacman;
    KeyBoardAgent* keyboard;
    std::vector<Agent*> agents;
    int currentMover;
    Game(std::vector<Agent*> agents,Layout* lay,bool learn,bool orig);
    bool learn;
    bool originalMode;
    QTimer* ghostModeTimer;
    void setGhostsToScatter(std::vector<Agent*> ghosts);
};

#endif // GAME_H
