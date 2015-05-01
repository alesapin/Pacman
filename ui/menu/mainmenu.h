#ifndef MAINMENU_H
#define MAINMENU_H
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "engine/gameoptions.h"
#include "engine/game.h"
#include "ui/canvas.h"
#include <QFile>
#include <QDebug>
#include "settings.h"
#include "engine/util.h"
class MainMenu : public QWidget
{
    Q_OBJECT
public:
    MainMenu();
public slots:
    void startGame();
    void startSettings();
private:
    QPushButton* startButton;
    QPushButton* exitButton;
    QPushButton* settings;
    static const QString CONFIG_PATH;
    int cellSize;
    void setButtons(QVBoxLayout* layout);
};

#endif // MAINMENU_H
