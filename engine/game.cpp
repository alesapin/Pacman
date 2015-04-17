#include "game.h"
#include <QDebug>


Game::Game(std::string layoutPath)
{
    Util::setSeed();
    layout = new Layout(layoutPath);
    currentGameState = new GameState(*layout);
    startState = currentGameState;
    currentMover = 0;
    setAgents();
}

GameState *Game::step()
{
    Agent* currentAgent;
    Direction action = NOACTION;
    if(currentMover == 0){
        currentAgent = pacman;
        GameState* observation = pacman->observationFuction(*currentGameState);
        action = pacman->getAction(*observation);
    }else{
        currentAgent = agents[currentMover-1];
        action = currentAgent->getAction(*currentGameState);
    }
    GameState* newState = currentGameState->generateSuccessor(currentMover,action);
    if(currentGameState != startState && !newState->isLose()){
        delete currentGameState;
    }
    currentMover = (currentMover+1)%(agents.size()+1);
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
    pacman->final(*currentGameState);
    delete currentGameState;
    currentGameState = startState;
    currentMover = 0;
    pacman->startEpisode(*startState);
}

bool Game::isLearning()
{
    return pacman->isTraining();
}

void Game::trainAgent()
{
    while(isLearning()){
        //qDebug()<<"УЧИТСЯ!";
        Agent* currentAgent;
        Direction action = NOACTION;
        if(currentMover == 0){
            currentAgent = pacman;
            GameState* observation = pacman->observationFuction(*currentGameState);
            action = pacman->getAction(*observation);
        }else{
            currentAgent = agents[currentMover-1];
            action = currentAgent->getAction(*currentGameState);
        }
        GameState* newState = currentGameState->generateSuccessor(currentMover,action);
        if(currentGameState != startState && !newState->isLose() && !newState->isWin()){
            delete currentGameState;
        }
        currentGameState = newState;
        currentMover = (currentMover+1)%(agents.size()+1);
        if(newState->isLose() || newState->isWin()){
//            qDebug() << "Пытаемся рестартнуть";
//            qDebug() << "Набрали очков:"<<newState->getScore();
            restartGame();
        }

    }
}



void Game::setAgents()
{
    //agents.push_back(new AlphaBetaAgent(3));
    pacman= new FeaturePacmanAgent(*startState,100,0.05,0.2,0.8);
    for(int i = 1; i < currentGameState->getAgentStates().size();++i){
        agents.push_back(new RushGhostAgent(i));
    }
}
