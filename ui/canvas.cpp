#include "canvas.h"
#include <QDebug>

Canvas::Canvas(GameOptions& opts):
    pacman(0),
    pause(false),
    gameOver(false)
{
    small = false;
    cellSize = opts.cellSize;
    setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);
    //setCacheMode(QGraphicsView::CacheBackground);
    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    myScene = new QGraphicsScene();
    this->setStyleSheet(ResourceLoader::STYLE);
    setScene(myScene);
    opts.scene = myScene;
    game = Game::parseOptions(opts);
    Layout* layout = game->getLayout();
    setScoreText(layout);
    QRectF sceneR = countSceneRect(layout);
    scene()->setSceneRect(sceneR);
    setGeometry(0,0,sceneR.bottomRight().x(),sceneR.bottomRight().y());
    setWalls(layout);
    setFoodMap(layout->getFood());
    setCapsuleMap(layout->getCapsules());
    agentTime = ResourceLoader::AGENT_TIMER_TIME;
    setAgents(layout);
    generalTime = ResourceLoader::GLOBAL_TIMER_TIME / (ghosts.size()+1);
    setRestartButton(layout);
    setPauseButton(layout);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(gameLoop()));
    connect(restartButton,SIGNAL(clicked()),this,SLOT(restartGame()));
    connect(pauseButton,SIGNAL(clicked()),this,SLOT(pauseGame()));
    delete &opts;
    if(game->isLearning()){
        setEnabled(false);
        TrainingWindow* train = new TrainingWindow(game,this);
        train->show();
        train->raise();
        train->activateWindow();
    }else{
        startGame();
    }
    Util::center(*this);

}

void Canvas::drawState(GameState *state)

{
    if(state->isWin() || state->isLose()){
        timer->stop();
        gameOver = true;
    }
    QPointF pos = state->getAgentPosition(0);

    pacman->moveToPoint(QPointF(pos.y()*cellSize,pos.x()*cellSize),state->getAgentState(0).getDireciton());
    for(int i = 0;i<ghosts.size();++i){
        GhostItem* currentGhost = ghosts[i];
        QPointF ghostPos = state->getAgentPosition(i+1);
        currentGhost->moveToPoint(QPointF(ghostPos.y()*cellSize,ghostPos.x()*cellSize),state->getAgentState(i+1).getDireciton());
        if (state->isScared(i+1)) {
            currentGhost->scarryMode();
        } else {
            currentGhost->normalMode();
        }
    }
    QPointF eatenFood = state->getEatenFood();
    if(foodMap.find(eatenFood)!=foodMap.end()){
        scene()->removeItem(foodMap[eatenFood]);
        delete foodMap[eatenFood];
        foodMap.erase(eatenFood);
    }
    QPointF eatenCapsule = state->getEatenCapsule();
    if(capsuleMap.find(eatenCapsule)!=capsuleMap.end()){
        scene()->removeItem(capsuleMap[eatenCapsule]);
        delete capsuleMap[eatenCapsule];
        capsuleMap.erase(eatenCapsule);
    }
    scoreText->updateScore(state->getScore());
}

void Canvas::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape){
        //MainMenu *m = new MainMenu();
        this->setDisabled(true);
        GamePauseMenu* p = new GamePauseMenu(this);
        pause = false;
        this->pauseGame();
        p->show();
    }else{
        game->keyBoardEvent(event);
    }
}

void Canvas::closeEvent(QCloseEvent *event)
{
    if(this->isEnabled()){
        event->accept();
    }else{
        event->ignore();
    }
}

int Canvas::getCellSize() const
{
    return cellSize;
}

void Canvas::unpause()
{
    pause = false;
    if(!gameOver) timer->start(generalTime);
    pauseButton->setText("pause");
}

QString Canvas::getScore() const
{
    return scoreText->text();
}

void Canvas::startGame()
{
    setEnabled(true);
    scene()->update();
    timer->start(generalTime);
}
//Раскоментить в будущем
//Canvas::~Canvas()
//{
//    scene()->clear();
//    delete game;
//    delete timer;
//    delete myScene;
//}

void Canvas::gameLoop()
{
    drawState(game->step());
    if(gameOver){
        this->setEnabled(false);
        GameOverMenu* go = new GameOverMenu(this);
        go->show();
    }
}

void Canvas::pauseGame()
{
    if(pause){
        pauseButton->setText("pause");
        if(!gameOver) timer->start(generalTime);
    }else{
        pauseButton->setText("unpause");
        timer->stop();
    }
    pause = !pause;
    //game->setFocus();
}

void Canvas::restartGame()
{
    gameOver = false;
    game->restartGame();
    Layout* layout = game->getLayout();
    setFoodMap(layout->getFood());
    setCapsuleMap(layout->getCapsules());
    setAgents(layout);
    scoreText->updateScore(0);
    if(!timer->isActive() && !pause){
        timer->start(generalTime);
    }
    //game->setFocus();
}

QPointF Canvas::countTextCoords(Layout *lay)
{
    int width = lay->getWalls().size();
    int height = lay->getWalls()[0].size();

    double dy = width;
    double dx = height-(height/3.);
    return QPointF(dx*cellSize,dy*cellSize);
}

QRectF Canvas::countSceneRect(Layout *lay)
{
    int width = lay->getWalls().size();
    int height = lay->getWalls()[0].size();
    double dy = width*cellSize+cellSize*1.5;
    double dx = height*cellSize-cellSize;
    if(small){
        dy =  width*cellSize+cellSize*3;
    }
    return QRectF(0,0,dx,dy);
}

QPointF Canvas::countRestartRect(Layout *lay)
{
    int width = lay->getWalls().size();
    int height = lay->getWalls()[0].size();
    int dy = width*cellSize;
    int dx = cellSize/3;
    return QPointF(dx,dy);
}


void Canvas::setCapsuleMap(std::vector<QPointF> caps)
{
    for(auto iter=capsuleMap.begin();iter!=capsuleMap.end();++iter){
        if(iter->second != 0){
            scene()->removeItem(iter->second);
           delete iter->second;
        }
    }
    for(auto p:caps){
        capsuleMap[p] = new QGraphicsEllipseItem(p.y()*cellSize+cellSize/4,p.x()*cellSize+cellSize/4,cellSize/2,cellSize/2);
        capsuleMap[p]->setBrush(QBrush(Qt::white));
        scene()->addItem(capsuleMap[p]);
    }
}


void Canvas::setFoodMap(std::vector<std::vector<bool> > foodTable)
{
    for(auto iter=foodMap.begin();iter!=foodMap.end();++iter){
        if(iter->second != 0){
            scene()->removeItem(iter->second);
            delete iter->second;
        }
    }
    for(int i=0;i<foodTable.size();++i){
        for(int j=0;j<foodTable[0].size();++j){
            if(foodTable[i][j]){
                QPointF p(i,j);
                foodMap[p] = new QGraphicsEllipseItem(p.y()*cellSize+cellSize/2,p.x()*cellSize+cellSize/2,cellSize/5,cellSize/5);
                foodMap[p]->setBrush(QBrush(Qt::white));
                scene()->addItem(foodMap[p]);
            }
        }
    }
}

void Canvas::setAgents(Layout *layout)
{
    if(pacman != 0){
        scene()->removeItem(pacman);
        delete pacman;
        pacman = 0;
    }
    if(!ghosts.empty()){
        for(auto ghost:ghosts){
            scene()->removeItem(ghost);
            delete ghost;
        }
        ghosts.clear();
    }
    pacman = new PacmanItem(layout->getPacmanPosition(),cellSize,agentTime);
    scene()->addItem(pacman);
    std::vector<QPointF> agentPositions = layout->getAgentsPositions();
    for(int i = 1; i< agentPositions.size();++i){
        GhostItem* ghost = new GhostItem(agentPositions[i],cellSize,agentTime,i);
        scene()->addItem(ghost);
        ghosts.push_back(ghost);
    }
}

void Canvas::setScoreText(Layout *lay)
{
    scoreText = new ScoreText(countTextCoords(lay),cellSize,lay->getWalls()[0].size());
    scoreText->updateScore(0);
    scene()->addItem(scoreText);
}

void Canvas::setWalls(Layout *layout)
{
    wallPainter = new WallItem(layout->getWalls(),cellSize,Qt::blue,cellSize/10);
    scene()->addItem(wallPainter);
}

void Canvas::setRestartButton(Layout *layout)
{
    double width = layout->getWalls()[0].size();
    restartButton = new QPushButton(this);
    restartButton->setObjectName("restartButton");
    restartButton->setText("restart");
    double fontSize = width > cellSize? cellSize/1.5:width;
    restartButton->setFont(QFont(ResourceLoader::FONT_NAME,fontSize));
    restartButton->setFocusPolicy(Qt::NoFocus);
    QPointF buttonPos = countRestartRect(layout);
    restartButton->setGeometry(buttonPos.x(),buttonPos.y(),cellSize/5,cellSize);

    restartButton->setMinimumWidth((width*cellSize)/6);
    restartButton->setMaximumWidth((width*cellSize)/3);
    scene()->addWidget(restartButton);
}

void Canvas::setPauseButton(Layout *layout)
{
    double width = layout->getWalls()[0].size();
    pauseButton = new QPushButton(this);
    pauseButton->setObjectName("pauseButton");
    pauseButton->setText("pause");
    double fontSize = width > cellSize? cellSize/1.5:width;
    pauseButton->setFont(QFont(ResourceLoader::FONT_NAME,fontSize));
    pauseButton->setFocusPolicy(Qt::NoFocus);
    QPointF buttonPos = countRestartRect(layout);
    pauseButton->setGeometry(buttonPos.x()+width*cellSize/3.,buttonPos.y(),cellSize/5,cellSize);
    pauseButton->setMinimumWidth((width*cellSize)/6.);
    pauseButton->setMaximumWidth((width*cellSize)/3.);
    scene()->addWidget(pauseButton);
}
