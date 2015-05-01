#ifndef GAMEPAUSEMENU_H
#define GAMEPAUSEMENU_H
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QObject>
#include "ui/canvas.h"
#include "mainmenu.h"
#include "engine/util.h"
class Canvas;
class GamePauseMenu: public QWidget
{
    Q_OBJECT
public:
    GamePauseMenu(Canvas* cnv);
    void paintEvent(QPaintEvent *);
public slots:
    void resumeGame();
    void returnToMenu();
private:
    QPushButton* resume;
    QPushButton* toMenu;
    Canvas* canvas;
};

#endif // GAMEPAUSEMENU_H
