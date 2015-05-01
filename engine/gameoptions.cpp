#include "gameoptions.h"


void GameOptions::createDefaultCfg(QFile &f)
{
    f.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);

    QTextStream out(&f);
    out << "layoutPath=layouts/originalClassic.lay" << '\n';
    out << "pacmanAgent=KEYBOARD" << '\n';
    out << "ghostAgent=RANDOM" << '\n';
    out << "cellSize=30"<<'\n';
    f.close();
}

GameOptions *GameOptions::parseFromFile(QFile& f)
{
    GameOptions* opts = new GameOptions();
    if(!f.exists()){
       createDefaultCfg(f);
    }
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&f);
    QString tmp;
    tmp = in.readLine();
    opts->layoutPath = tmp.split("=").value(1);
    tmp = in.readLine();
    opts->pacmanAgent = tmp.split("=").value(1);
    if(opts->pacmanAgent == Game::LEARNING){
        tmp = in.readLine();
        opts->alpha = tmp.split("=").value(1).toDouble();
        tmp = in.readLine();
        opts->epsilon = tmp.split("=").value(1).toDouble();
        tmp = in.readLine();
        opts->gamma =tmp.split("=").value(1).toDouble();
        tmp = in.readLine();
        opts->numIters = tmp.split("=").value(1).toInt();
    }else if (opts->pacmanAgent == Game::MINIMAX || opts->pacmanAgent == Game::EXPECTIMAX){
        tmp=in.readLine();
         opts->minimaxDepth = tmp.split("=").value(1).toInt();
    }
    tmp = in.readLine();
    opts->ghostAgent = tmp.split("=").value(1);
    tmp=in.readLine();
    opts->cellSize = tmp.split("=").value(1).toInt();
    return opts;
}
