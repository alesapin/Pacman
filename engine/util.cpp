#include "util.h"

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
    for(int i=1;i<vect.size();++i){
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

double Util::closestFood(QPointF currentPosition, const std::vector<std::vector<bool> > &food, const std::vector<std::vector<bool> > &walls)
{
    std::deque<std::tuple<QPointF,double>> fringe;
    fringe.push_back(std::make_tuple(currentPosition,0));
    std::set<QPointF,PointComparator> expanded;
    while(!fringe.empty()){
        std::tuple<QPointF,double> current = fringe.front();
        fringe.pop_front();
        QPointF pos = std::get<0>(current);
        double dist = std::get<1>(current);
        if(expanded.find(pos)!=expanded.end()){
            continue;
        }
        expanded.insert(pos);
        if(food[pos.x()][pos.y()]){
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

