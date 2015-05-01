#ifndef GAMEOVERMENU_H
#define GAMEOVERMENU_H
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QObject>
#include <QLabel>
#include "ui/canvas.h"
#include "mainmenu.h"
#include "engine/util.h"
class Canvas;
class GameOverMenu: public QWidget
{
    Q_OBJECT
public:
    GameOverMenu(Canvas* cnv);
    void paintEvent(QPaintEvent *);
public slots:
    void restartGame();
    void exitToMenu();
private:
    Canvas* canvas;
    QLabel* gameOver;
    QLabel* score;
    QPushButton* restart;
    QPushButton* toMenu;
};

#endif // GAMEOVERMENU_H
