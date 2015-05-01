#include "game.h"
#include <QDebug>


const QString Game::LEARNING = "LEARNING";
const QString Game::MINIMAX = "MINIMAX";
const QString Game::EXPECTIMAX = "EXPECTIMAX";
const QString Game::RUSH = "RUSH";
const QString Game::RANDOM = "RANDOM";
const QString Game::KEYBOARD = "KEYBOARD";

Game::Game(std::vector<Agent *> agents, Layout *lay,bool learn):
    agents(agents),
    currentMover(0),
    learn(learn)
{
    if(learn){
        pacman = static_cast<PacmanLearningAgent*>(agents[0]);
    }
    keyboard = dynamic_cast<KeyBoardAgent*>(agents[0]);
    layout = lay;
    currentGameState = new GameState(layout);
    startState = currentGameState;
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

Game *Game::parseOptions(GameOptions& opts)
{
    bool learn = false;
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
        for(int i = 1;i<lay->getAgentsPositions().size();++i){
            agents.push_back(new RushGhostAgent(i));
        }
    } else if(opts.ghostAgent == Game::RANDOM){
        for(int i = 1;i<lay->getAgentsPositions().size();++i){
            agents.push_back(new RandomGhostAgent(i));
        }
    }
    return new Game(agents,lay,learn);

}


