#ifndef TRAININGWINDOW_H
#define TRAININGWINDOW_H
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QObject>
#include <QLabel>
#include <QProgressBar>
#include "ui/canvas.h"
#include "engine/game.h"
#include "mainmenu.h"
#include "engine/util.h"
class TrainingWindow: public QWidget
{
    Q_OBJECT
public:
    TrainingWindow(Game* g,Canvas* can);
    bool isFinished();
    void paintEvent(QPaintEvent *);

public slots:
    void trainLoop();
    void stopTrain();
private:
    Game* game;
    Canvas* canvas;
    QLabel* text;
    QProgressBar* bar;
    QTimer* learnTimer;
    bool finished;
    QPushButton* stop;
};

#endif // TRAININGWINDOW_H
