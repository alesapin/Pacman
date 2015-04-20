#include "canvas.h"
#include <QDebug>

Canvas::Canvas(GameOptions opts, int cs):
    cellSize(cs),
    pacman(0)
{
    setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);
    setCacheMode(QGraphicsView::CacheNone);
    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    QFontDatabase::addApplicationFont(":/fonts/Munro.ttf");

    myScene = new QGraphicsScene();
    this->setStyleSheet("background-color: black;");
    setScene(myScene);


    game = Game::parseOptions(opts);
    Layout* layout = game->getLayout();
    scene()->setSceneRect(countSceneRect(layout));

    setWalls(layout);
    setScoreText(layout);
    setFoodMap(layout->getFood());
    setCapsuleMap(layout->getCapsules());
    setAgents(layout);
    setRestartButton(layout);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(gameLoop()));
    connect(restartButton,SIGNAL(clicked()),this,SLOT(restartGame()));
    timer->start(50);
    counter  = 0 ;
    game->trainAgent();
}

void Canvas::drawState(GameState *state)

{
    std::vector<Direction> legal= state->getLegalPacmanActions();

    if(state->isWin() || state->isLose()){
        timer->stop();
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

void Canvas::gameLoop()
{
    drawState(game->step());
    scene()->update(scene()->sceneRect());
}

void Canvas::restartGame()
{

    game->restartGame();
    Layout* layout = game->getLayout();
    setFoodMap(layout->getFood());
    setCapsuleMap(layout->getCapsules());
    setAgents(layout);
    if(!timer->isActive()){
        timer->start(50);
    }
}

QPointF Canvas::countTextCoords(Layout *lay)
{
    int width = lay->getWalls().size();
    int height = lay->getWalls()[0].size();
    int dy = width*cellSize;
    int dx = height*cellSize-(height/3)*cellSize;
    return QPointF(dx,dy);
}

QRectF Canvas::countSceneRect(Layout *lay)
{
    int width = lay->getWalls().size();
    int height = lay->getWalls()[0].size();
    int dy = width*cellSize+cellSize*3/2;
    int dx = height*cellSize-cellSize;
    return QRectF(0,0,dx,dy);
}

QPointF Canvas::countRestartRect(Layout *lay)
{
    int width = lay->getWalls().size();
    int height = lay->getWalls()[0].size();
    int dy = width*cellSize;
    int dx = cellSize;
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
        capsuleMap[p] = new QGraphicsEllipseItem(p.y()*cellSize,p.x()*cellSize,cellSize,cellSize);
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
    pacman = new PacmanItem(layout->getPacmanPosition(),cellSize,10);
    scene()->addItem(pacman);
    std::vector<QPointF> agentPositions = layout->getAgentsPositions();
    for(int i = 1; i< agentPositions.size();++i){
        GhostItem* ghost = new GhostItem(agentPositions[i],cellSize,10,i);
        scene()->addItem(ghost);
        ghosts.push_back(ghost);
    }
}

void Canvas::setScoreText(Layout *lay)
{
    scoreText = new ScoreText(countTextCoords(lay),cellSize);
    scene()->addItem(scoreText);
}

void Canvas::setWalls(Layout *layout)
{
    wallPainter = new WallItem(layout->getWalls(),cellSize,Qt::blue,cellSize/10);
    scene()->addItem(wallPainter);
}

void Canvas::setRestartButton(Layout *layout)
{
    QFile style(":/stylesheets/stylesheets/button.qss"); //move to resouce loader
    style.open(QFile::ReadOnly);
    QString str = QLatin1String(style.readAll());
    restartButton = new QPushButton();
    restartButton->setObjectName("restartButton");
    restartButton->setText("restart");
    restartButton->setStyleSheet(str);
    restartButton->setFont(QFont("Munro",cellSize/1.5));
    restartButton->setFocusPolicy(Qt::NoFocus);
    QPointF buttonPos = countRestartRect(layout);
    restartButton->setGeometry(buttonPos.x(),buttonPos.y(),cellSize/5,cellSize);
    scene()->addWidget(restartButton);
}
