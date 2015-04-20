#include "game.h"
#include <QDebug>


const std::string Game::LEARNING = "LEARNING_AGENT";
const std::string Game::MINIMAX = "MINIMAX_AGENT";
const std::string Game::EPECTIMAX = "EXPECTIMAX_AGENT";
const std::string Game::RUSH = "RUSH_AGENT";
const std::string Game::RANDOM = "RANDOM_AGENT";

Game::Game(std::vector<Agent *> agents, Layout *lay,bool learn):
    layout(lay),
    agents(agents),
    currentMover(0),
    learn(learn)
{
    if(learn){
        pacman = static_cast<PacmanLearningAgent*>(agents[0]);
    }
    currentGameState = new GameState(*layout);
    startState = currentGameState;
}

GameState *Game::step()
{
    Direction action = agents[currentMover]->getAction(*currentGameState);
    GameState* newState = currentGameState->generateSuccessor(currentMover,action);
    if(currentGameState != startState && !newState->isLose() && !newState->isWin()){
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
    delete currentGameState;
    currentGameState = startState;
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

Game *Game::parseOptions(GameOptions & opts)
{
    bool learn = false;
    std::vector<Agent*> agents;
    Layout* lay = new Layout(opts.layoutPath);
    if(opts.pacmanAgent == Game::LEARNING){
        learn = true;
        agents.push_back(new PacmanLearningAgent(opts.numIters,opts.epsilon,opts.alpha,opts.gamma));
    } else if(opts.pacmanAgent == Game::MINIMAX){
        agents.push_back(new AlphaBetaAgent(opts.minimaxDepth));
    } else if(opts.pacmanAgent == Game::EPECTIMAX){
        agents.push_back(new ExpectimaxAgent(opts.minimaxDepth));
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


