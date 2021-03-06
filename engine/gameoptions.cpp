#include "gameoptions.h"


GameOptions *GameOptions::parseFromFile()
{
    QSettings *settings = new QSettings(ResourceLoader::CONFIG_PATH,QSettings::NativeFormat);
    GameOptions* opts = new GameOptions();
    opts->layoutPath = settings->value("layoutPath","layouts/smallClassic.lay").toString() ;
    opts->pacmanAgent = settings->value("pacmanAgent","KEYBOARD").toString();
    if(opts->pacmanAgent == Game::LEARNING){
        opts->alpha = settings->value("alpha",0.2).toDouble();
        opts->epsilon = settings->value("epsilon",0.05).toDouble();
        opts->gamma = settings->value("gamma",0.8).toDouble();
        opts->numIters = settings->value("numIters",50).toInt();
    }else if (opts->pacmanAgent == Game::MINIMAX || opts->pacmanAgent == Game::EXPECTIMAX){
         opts->minimaxDepth = settings->value("maxDepth",2).toInt();
    }
    opts->ghostAgent = settings->value("ghostAgent","RANDOM").toString();
    opts->cellSize = settings->value("cellSize",30).toInt();
    opts->gameSpeed=settings->value("gameSpeed",150).toInt();
    opts->sound = settings->value("sound",false).toBool();
    return opts;
}
