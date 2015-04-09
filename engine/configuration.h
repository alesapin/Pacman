#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <QPointF>
enum Direction{
    NORTH,SOUTH,EAST,WEST,STOP
};
class Configuration
{
public:
    Configuration(QPointF pos,Direction dir);
    Configuration(const Configuration& config);
    bool isInteger();
    Direction getDirection();
    QPointF getPosition();
    bool operator==(const Configuration& other);
    Configuration generateSuccessor(QPointF vectorTo);
private:
    Direction direction;
    QPointF position;
};

#endif // CONFIGURATION_H
