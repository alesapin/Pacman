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
    return std::floor(position.x())==position.x() && std::floor(position.y()) == position.y();
}

Direction Configuration::getDirection() const
{
    return direction;
}

QPointF Configuration::getPosition() const
{
    return position;
}

void Configuration::setPosition(QPointF p)
{
    position = p;
}

bool Configuration::operator==(const Configuration &other)
{
    return direction==other.direction && position==other.position;
}

Configuration Configuration::generateSuccessor(QPointF vectorTo)
{
    //QDebug debug = qDebug();
    double x =position.x();
    double y = position.y();
    double dx = vectorTo.x();
    double dy = vectorTo.y();

    Direction dir = Actions::vectorToDirection(vectorTo);
    if (dir == STOP){
        dir = direction;
    }
    return Configuration(QPointF(x+dx,y+dy),dir); //TODO
}

