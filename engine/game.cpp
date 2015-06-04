#include "game.h"
#include <QDebug>


const QString Game::LEARNING = "LEARNING";
const QString Game::MINIMAX = "MINIMAX";
const QString Game::EXPECTIMAX = "EXPECTIMAX";
const QString Game::RUSH = "RUSH";
const QString Game::RANDOM = "RANDOM";
const QString Game::KEYBOARD = "KEYBOARD";
const QString Game::DIRECTIONAL = "DIRECTIONAL";
const QString Game::ORIGINAL = "ORIGINAL";

Game::Game(std::vector<Agent *> agents, Layout *lay,bool learn,bool orig):
    agents(agents),
    currentMover(0),
    learn(learn),
    originalMode(orig)
{
    if(learn){
        pacman = static_cast<PacmanLearningAgent*>(agents[0]);
    }
    keyboard = dynamic_cast<KeyBoardAgent*>(agents[0]);
    layout = lay;
    currentGameState = new GameState(layout);
    startState = currentGameState;
    pause = false;
    if(orig){
        ghostModeTimer = new QTimer();
        connect(ghostModeTimer,SIGNAL(timeout()),this,SLOT(switchMode()));
        scatterTime = 5000;
        chaseTime = 20000;
        ghostModeTimer->start(scatterTime);
    }

}
bool Game::getPause() const
{
    return pause;
}

void Game::setPause(bool value)
{
    pause = value;
    if(originalMode){
        if(pause){
            ghostModeTimer->stop();
        }else{
            DirectionalGhostAgent* ghost =  static_cast<DirectionalGhostAgent*>(agents[1]);
            if(ghost->getMode() == SCATTER){
                ghostModeTimer->start(scatterTime);
            }else{
                ghostModeTimer->start(chaseTime);
            }
        }
    }
}


void Game::setGhostsToScatter(std::vector<Agent *> ghosts)
{
    for(std::size_t i = 1;i<ghosts.size();++i){
        DirectionalGhostAgent* agent = static_cast<DirectionalGhostAgent*>(ghosts[i]);
        agent->setMode(SCATTER);
    }
}

GameState *Game::step()
{
    Direction action = agents[currentMover]->getAction(*currentGameState);
    GameState* newState = currentGameState->generateSuccessor(currentMover,action);
    if(currentGameState != startState){
        delete currentGameState;
    }
    currentMover = (currentMover+1)%(agents.size());
    return currentGameState = newState;
}

Layout *Game::getLayout()
{
    return layout;
}

Game::~Game()
{
    delete layout;
    delete currentGameState;
    delete startState;
    for(Agent* agent:agents){
        delete agent;
    }
}

void Game::restartGame()
{
    if(learn){
        pacman->final(*currentGameState);
        pacman->startEpisode();
    }
    if(currentGameState != startState){
        delete currentGameState;
        currentGameState = startState;
    }
    if(keyboard!=0){
        keyboard->setDirection(STOP);
    }
    if(originalMode){
        scatterTime = 5000;
        chaseTime = 20000;
        setGhostsToScatter(agents);
        ghostModeTimer->stop();
        ghostModeTimer->start(scatterTime);
    }
    currentMover = 0;
}

bool Game::isLearning()
{
    if(learn){
        return pacman->isTraining();
    }else{
        return false;
    }
}

void Game::trainAgent()
{
    while(isLearning()){
        step();
        if(currentGameState->isLose() || currentGameState->isWin()){
            restartGame();
        }
    }
    learn = false;
}

void Game::setFocus()
{
    if(keyboard!=0){
        keyboard->setFocus();
    }
}

void Game::keyBoardEvent(QKeyEvent *event)
{
    if(keyboard!=0){
        keyboard->keyPressEvent(event);
    }
}

int Game::getTotalIters() const
{
    if(learn){
        return pacman->getTotalNumIters();
    }else{
        return 0;
    }
}

int Game::trainStep()
{
    if(isLearning()){
        step();
        if(currentGameState->isLose() || currentGameState->isWin()){
            restartGame();
        }
        return pacman->getTrainIteration();
    }else{
        return 0;
    }
}

void Game::switchMode()
{
    ghostModeTimer->stop();
    if(!pause){
        DirectionalGhostAgent* ghost;
        for(std::size_t i = 1; i<agents.size();++i){
            ghost =  static_cast<DirectionalGhostAgent*>(agents[i]);
            ghost->changeMode();
        }
        qDebug()<<"MODE SWITCHED TO "<< ghost->getMode();
        if(scatterTime <= 0 && ghost->getMode() == CHASE){
            return;
        }
        chaseTime+=1000;
        scatterTime-=1000;
        if(ghost->getMode() == CHASE){
            ghostModeTimer->start(chaseTime);
        }else{
            ghostModeTimer->start(scatterTime);
        }
    }
}

Game *Game::parseOptions(GameOptions& opts)
{
    bool learn = false;
    bool orig = false;
    std::vector<Agent*> agents;
    Layout* lay = new Layout(opts.layoutPath);
    if(opts.pacmanAgent == Game::LEARNING){
        learn = true;
        agents.push_back(new PacmanLearningAgent(opts.numIters,opts.epsilon,opts.alpha,opts.gamma));
    } else if(opts.pacmanAgent == Game::MINIMAX){
        agents.push_back(new AlphaBetaAgent(opts.minimaxDepth));
    } else if(opts.pacmanAgent == Game::EXPECTIMAX){
        agents.push_back(new ExpectimaxAgent(opts.minimaxDepth));
    } else if(opts.pacmanAgent == Game::KEYBOARD){
        KeyBoardAgent* agent = new KeyBoardAgent();
        opts.scene->addItem(agent);
        agents.push_back(agent);
    }

    if(opts.ghostAgent == Game::RUSH){
        for(std::size_t i = 1;i<lay->getAgentsPositions().size();++i){
            agents.push_back(new RushGhostAgent(i));
        }
    } else if(opts.ghostAgent == Game::RANDOM){
        for(std::size_t i = 1;i<lay->getAgentsPositions().size();++i){
            agents.push_back(new RandomGhostAgent(i));
        }
    } else if (opts.ghostAgent == Game::ORIGINAL){
        if(lay->getAgentsPositions().size() > 1){
            DirectionalGhostAgent *agent = new BlinkyGhostAgent(DirectionalGhostAgent::BLINKY_NUMBER);
            agent->setMode(SCATTER);
            agents.push_back(agent);
        }
        if(lay->getAgentsPositions().size() > 2){
            DirectionalGhostAgent* agent = new PinkyGhostAgent(DirectionalGhostAgent::PINKY_NUMBER);
            agent->setMode(SCATTER);
            agents.push_back(agent);
        }
        if(lay->getAgentsPositions().size() > 3){
            DirectionalGhostAgent* agent = new PinkyGhostAgent(DirectionalGhostAgent::INKY_NUMBER);
            agent->setMode(SCATTER);
            agents.push_back(agent);
        }
        if(lay->getAgentsPositions().size() > 4){
            DirectionalGhostAgent* agent = new ClydeGhostAgent(DirectionalGhostAgent::CLYDE_NUMBER);
            agent->setMode(SCATTER);
            agents.push_back(agent);
        }
        orig = true;
    }else if (opts.ghostAgent == Game::DIRECTIONAL){
        for(std::size_t i = 1;i<lay->getAgentsPositions().size();++i){
            agents.push_back(new DirectionalGhostAgent(i));
        }
    }
    return new Game(agents,lay,learn,orig);

}


