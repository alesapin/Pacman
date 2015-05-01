#include "keyboardagent.h"

KeyBoardAgent::KeyBoardAgent()
{
    currentDirection = STOP;
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

Direction KeyBoardAgent::getAction(GameState& state)
{
    return currentDirection;
}

void KeyBoardAgent::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left){
        currentDirection = WEST;
    }else if (event->key() == Qt::Key_Right) {
        currentDirection = EAST;
    }else if (event->key() == Qt::Key_Up) {
        currentDirection = NORTH;
    }else if (event->key() == Qt::Key_Down){
        currentDirection = SOUTH;
    }
}

void KeyBoardAgent::setDirection(Direction dir)
{
    currentDirection = dir;
}
