#include "actions.h"
#include <QDebug>

Direction Actions::reverseDirection(Direction direction)
{
    switch (direction) {
    case NORTH:
        return SOUTH;
        break;
    case SOUTH:
        return NORTH;
        break;
    case WEST:
        return EAST;
        break;
    case EAST:
        return WEST;
        break;
    default:
        return STOP;
        break;
    }
}

std::map<Direction,QPointF> Actions::directions = {
    {WEST,QPointF(0,-1)},
    {EAST,QPointF(0,1)},
    {SOUTH,QPointF(1,0)},
    {NORTH,QPointF(-1,0)},
    {STOP,QPointF(0,0)}
};
const double Actions::TOLERANCE = 0.001;
Direction Actions::vectorToDirection(QPointF vect)
{
    double dx = vect.x();
    double dy = vect.y();
    if (dy > 0) return EAST;
    if (dy < 0) return WEST;
    if (dx < 0) return NORTH;
    if (dx > 0) return SOUTH;
    return STOP;
}

QPointF Actions::directionToVector(Direction dir, double speed)
{
//    if(dir == NOACTION){
//        qDebug() <<"";
//    }
    QPointF p = directions[dir];
    double dx = p.x();
    double dy = p.y();
    return QPointF(dx*speed,dy*speed);
}

std::vector<Direction> Actions::getPossibleActions(Configuration& config,const std::vector<std::vector<bool> >& walls)
{
//    QDebug debug = qDebug();
    std::vector<Direction> result;
    QPointF pos = config.getPosition();
    double x = pos.x();
    double y = pos.y();
//    debug <<"X:"<< x;
//    debug <<"Y:"<<y;
//    debug<<"\n";
    int intx = (int)(x+0.5);
    int inty = (int)(y+0.5);
    if (std::abs(x-intx)+std::abs(y-inty) > TOLERANCE){
        result.push_back(config.getDirection());
        return result;
    }
    for (auto iter = directions.begin();iter != directions.end();++iter){
        Direction currentDirection = iter->first;
        if(currentDirection == STOP) continue;
        QPointF currentVector = iter->second;
        double dx = currentVector.x();
        double dy = currentVector.y();
        double nextX = x + dx;
        double nextY = y + dy;
        double indX = (int)(nextX+0.5);
        double indY = (int)(nextY+0.5);

        if (nextX < 0 || nextX >= walls.size()) continue;
        if(nextY < 0 || nextY >= walls[0].size()) continue;
        if (!walls[indX][indY]) result.push_back(currentDirection);
    }
    result.push_back(STOP);
    return result;
}

std::vector<QPointF> Actions::getLegalNeighbours(QPointF position, const std::vector<std::vector<bool> >& walls)
{
    double x =position.x();
    double y = position.y();
    int intx= (int)(x+0.5);
    int inty = (int)(y+0.5);
    std::vector<QPointF> result;
    for (auto iter = directions.begin();iter != directions.end();++iter){
        QPointF currentVector = iter->second;
        double dx = currentVector.x();
        double dy = currentVector.y();
        int nextX = (int)(intx+dx);
        if (nextX < 0 || nextX >= walls.size()) continue;
        int nextY = (int)(inty+dy);
        if(nextY < 0 || nextY >= walls[0].size()) continue;
        if (!walls[nextX][nextY]){
            result.push_back(QPointF(nextX,nextY));
        }
    }
    return result;
}

QPointF Actions::getSuccessor(QPointF point, Direction dir)
{
    QPointF shift = Actions::directionToVector(dir);
    double dx = shift.x();
    double dy = shift.y();
    double x = point.x();
    double y = point.y();
    return QPointF(x+dx,y+dy);

}
