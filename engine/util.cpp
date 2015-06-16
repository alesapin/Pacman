#include "util.h"
#include "ghostrules.h"
#include <QDebug>
double Util::manhattanDistance(QPointF f, QPointF s)
{
    return std::abs(f.x()-s.x())+std::abs(f.y()-s.y());
}

int Util::maxIndex(std::vector<double> vect)
{
    if(vect.empty()){
        return -1;
    }
    int maxIndex = 0;
    int maxVal = vect[0];
    for(std::size_t i=1;i<vect.size();++i){
        if(vect[i] > maxVal){
            maxVal = vect[i];
            maxIndex = i;
        }
    }
    return maxIndex;
}

void Util::normalize(std::map<Direction, double> &dict)
{
    double sum = 0;
    for(auto it = dict.begin();it!=dict.end();++it){
        sum+= it->second;
    }
    for(auto it=dict.begin();it != dict.end();++it){
        it->second /= sum;
    }
}

bool Util::tossCoin(double prob)
{
    double r = Util::randDouble();
    return r < prob;
}

double Util::randDouble()
{
    return  ((double) rand() / (RAND_MAX));
}

QPointF Util::nearestIntPoint(QPointF p)
{
    return QPointF((int)(p.x()+0.5),(int)(p.y()+0.5));
}

double Util::closestFood(QPointF currentPosition, const GameState &state)
{
    return closestObject(currentPosition,state,[&](QPointF p){return state.getFood()[p.x()][p.y()];});
}

double Util::closestCapsule(QPointF currentPosition, const GameState &state)
{
    return closestObject(currentPosition,state,[&](QPointF p){
        std::vector<QPointF> capsules = state.getCapsules();
        return (std::find(capsules.begin(),capsules.end(),p) != capsules.end());
    });

}

double Util::distToGhost(QPointF currentPosition, const GameState &state, QPointF ghostPos)
{
    return closestObject(currentPosition,state,[&](QPointF p){
        return currentPosition == ghostPos;
    });
}

double Util::closestObject(QPointF currentPosition, const GameState &state, std::function<bool (QPointF)> predicate)
{
    std::deque<std::tuple<QPointF,double>> fringe;
    fringe.push_back(std::make_tuple(currentPosition,0));
    std::set<QPointF,PointComparator> expanded;
    auto walls = state.getLayout()->getWalls();
    while(!fringe.empty()){
        std::tuple<QPointF,double> current = fringe.front();
        fringe.pop_front();
        QPointF pos = std::get<0>(current);
        double dist = std::get<1>(current);
        if(expanded.find(pos)!=expanded.end()){
            continue;
        }
        expanded.insert(pos);
        if(predicate(pos)){
            return dist;
        }
        std::vector<QPointF> nbrs = Actions::getLegalNeighbours(pos,walls);
        for(QPointF nbr:nbrs){
            fringe.push_back(std::make_tuple(nbr,dist+1));
        }
    }
    return -1;
}

void Util::center(QWidget &widget ,int WIDTH , int HEIGHT)
{
        int x, y;
        int screenWidth;
        int screenHeight;

        QDesktopWidget *desktop = QApplication::desktop();

        screenWidth = desktop->width();
        screenHeight = desktop->height();

        x = (screenWidth - WIDTH) / 2;
        y = (screenHeight - HEIGHT) / 2;

        widget.setGeometry(x, y, WIDTH, HEIGHT);

}

void Util::center(QWidget &widget)
{
    center(widget,widget.width(),widget.height());
}

Direction Util::ghostWayToPoint(int ghostNumber, QPointF point, const GameState &state)
{
    std::deque<std::tuple<Configuration,Direction>> fringe;
    std::vector<Direction> legal = state.getLegalActions(ghostNumber);
    fringe.push_back(std::make_tuple(state.getAgentState(ghostNumber).getConfiguration(),legal[0]));
    std::set<QPointF,PointComparator> expanded;
    if(state.getLayout()->getWalls()[point.x()][point.y()]){
        point = emptyNearWall(point,state.getLayout()->getWalls());
    }
    bool firstStep = true;
    while(!fringe.empty()){
        std::tuple<Configuration,Direction> current = fringe.front();
        fringe.pop_front();
        Configuration conf = std::get<0>(current);
        QPointF pos = conf.getPosition();
        Direction startDirection = std::get<1>(current);
        if(expanded.find(pos)!=expanded.end()){
            continue;
        }
        expanded.insert(pos);
        if(pos == point){
            return startDirection;
        }

        std::vector<Direction> legal = GhostRules::getLegalActions(std::get<0>(current),state.getLayout()->getWalls());

        if(firstStep){
            for(Direction dir:legal){
                Configuration succ = conf.generateSuccessor(dir);
                fringe.push_back(std::make_tuple(succ,dir));
            }
            firstStep = false;
        }else{
            for(Direction dir:legal){
                Configuration succ = conf.generateSuccessor(dir);
                fringe.push_back(std::make_tuple(succ,startDirection));
            }
        }
    }

    return legal[rand()%legal.size()];
}

QPointF Util::emptyNearWall(QPointF point, const std::vector<std::vector<bool> > &walls)
{
    int x =(int) point.x();
    int y =(int) point.y();
    int width = walls.size();
    int height = walls[0].size();
    for(int i = 0; ;++i){
        if(x + i < width && !walls[x+i][y]) return QPointF(x+i,y);
        if(x - i > 0 && !walls[x-i][y]) return QPointF(x-i,y);
        if(y + i < height && !walls[x][y+i]) return QPointF(x,y+i);
        if(y - i > 0 && !walls[x][y-i]) return QPointF(x,y-i);
        if(x + i < width && y+i < height && !walls[x+i][y+i]) return QPointF(x+i,y+i);
        if(x - i > 0 &&  y + i < height && !walls[x-i][y+i]) return QPointF(x-i,y+i);
        if(x + i < width && y - i > 0 && !walls[x+i][y-i]) return QPointF(x+i,y-i);
        if(x - i > 0 && y - i > 0 && !walls[x-i][y-i]) return QPointF(x+i,y+i);
    }
}


