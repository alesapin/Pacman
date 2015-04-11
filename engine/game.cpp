#include "game.h"
#include <QDebug>


Game::Game(std::string layoutPath)
{
    layout = new Layout(layoutPath);
    currentGameState = new GameState(*layout);
    startState = currentGameState;
    currentMover = 0;
    setAgents();
}

GameState *Game::step()
{
    Agent* currentAgent = agents[currentMover];
    GameState* newState = currentGameState->generateSuccessor(currentMover,currentAgent->getAction(*currentGameState));
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



void Game::setAgents()
{
    agents.push_back(new AlphaBetaAgent(4));
    for(int i = 1; i < currentGameState->getAgentStates().size();++i){
        agents.push_back(new RushGhostAgent(i));
    }
}
