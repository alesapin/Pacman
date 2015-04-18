#ifndef GAMEOPTIONS_H
#define GAMEOPTIONS_H
#include <string>
struct GameOptions
{
    std::string pacmanAgent;
    std::string ghostAgent;
    std::string layoutPath;
    int numIters;
    double alpha;
    double epsilon;
    double gamma;
    int minimaxDepth;
};

#endif // GAMEOPTIONS_H
