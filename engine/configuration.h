#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <QPointF>
enum Direction{
    NORTH,SOUTH,EAST,WEST,STOP,NOACTION
};
class Configuration
{
public:
    Configuration(QPointF pos,Direction dir);
    Configuration(const Configuration& config);
    bool isInteger();
    Direction getDirection() const;
    QPointF getPosition() const;
    void setPosition(QPointF p);
    bool operator==(const Configuration& other);
    Configuration generateSuccessor(QPointF vectorTo);
    Configuration generateSuccessor(Direction dir);
private:
    Direction direction;
    QPointF position;
};

#endif // CONFIGURATION_H
