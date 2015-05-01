#ifndef CANVAS_H
#define CANVAS_H
#include <QWidget>
#include "wallitem.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include "engine/gamestate.h"
#include <map>
#include "engine/layout.h"
#include <vector>
#include <QGraphicsScene>
#include "pacmankeyboarditem.h"
#include <QTimer>
#include <QObject>
#include "pacmanitem.h"
#include "agents/expectimaxagent.h"
#include "ghostitem.h"
#include "agents/randomghostagent.h"
#include "agents/alphabetaagent.h"
#include "agents/rushghostagent.h"
#include "engine/game.h"
#include "scoretext.h"
#include <QFontDatabase>
#include <QPushButton>
#include "ui/menu/gamepausemenu.h"
#include "ui/menu/gameovermenu.h"
#include "ui/menu/trainingwindow.h"
class Canvas:  public QGraphicsView {
        Q_OBJECT
public:
    Canvas(GameOptions& opts);
    void drawState(GameState* state);
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);
    int getCellSize() const;
    void unpause();
    QString getScore() const;
    void startGame();
public slots:
    void gameLoop();
    void pauseGame();
    void restartGame();
private:
    std::map<QPointF,QGraphicsEllipseItem*,PointComparator> foodMap;
    std::map<QPointF,QGraphicsEllipseItem*,PointComparator> capsuleMap;
    WallItem* wallPainter;
    Game* game;
    ScoreText* scoreText;
    QPushButton* restartButton;
    QPushButton* pauseButton;
    PacmanItem* pacman;
    std::vector<GhostItem*> ghosts;
    QPointF countTextCoords(Layout* lay);
    QRectF countSceneRect(Layout* lay);
    QPointF countRestartRect(Layout* lay);
    void removeFood(QPointF foodPoint);
    void setCapsuleMap(std::vector<QPointF> caps);
    void setFoodMap(std::vector<std::vector <bool> > foodTable);
    void setAgents(Layout* lay);
    void setScoreText(Layout *lay);
    void setWalls(Layout* lay);
    void setRestartButton(Layout* lay);
    void setPauseButton(Layout* lay);
    int cellSize;
    bool pause;
    bool gameOver;
    QGraphicsScene * myScene;
    QTimer * timer;
    int counter;
    int generalTime;
    int agentTime;
    bool small;
};

#endif // CANVAS_H
