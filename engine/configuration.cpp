#include "configuration.h"
#include <cmath>
#include "actions.h"
#include <QDebug>


Configuration::Configuration(QPointF pos,Direction dir)
{
    direction = dir;
    position = pos;
}

Configuration::Configuration(const Configuration &config)
{
    direction = config.direction;
    position = config.position;
}

bool Configuration::isInteger()
{
    return std::floor(position.x())==position.x() && std::floor(position.y())==position.y();
}

Direction Configuration::getDirection()
{
    return direction;
}

QPointF Configuration::getPosition()
{
    return position;
}

bool Configuration::operator==(const Configuration &other)
{
    return direction==other.direction && position==other.position;
}

Configuration Configuration::generateSuccessor(QPointF vectorTo)
{
    double x =position.x();
    double y = position.y();
    double dx = vectorTo.x();
    double dy = vectorTo.y();
    Direction dir = Actions::vectorToDirection(vectorTo);
    if (dir == STOP){
        dir = direction;
    }
    return Configuration(QPointF(x+dx/4,y+dy/4),dir); //TODO
}

