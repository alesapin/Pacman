#ifndef KEYBOARDAGENT_H
#define KEYBOARDAGENT_H
#include "agent.h"
#include <QGraphicsRectItem>
#include <QKeyEvent>

class KeyBoardAgent : public Agent, public QGraphicsRectItem
{
public:
    KeyBoardAgent();
    Direction getAction(GameState& state);
    void keyPressEvent(QKeyEvent *event);
    void setDirection(Direction dir);
private:
    Direction currentDirection;
};

#endif // KEYBOARDAGENT_H
