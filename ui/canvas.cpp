#include "canvas.h"
#include <QDebug>

Canvas::Canvas(std::string path,int cs):
    cellSize(cs)
{
    setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);
    setCacheMode(QGraphicsView::CacheNone);
    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    myScene = new QGraphicsScene();
    this->setStyleSheet("background-color: black;");
    setScene(myScene);
    game = new Game(path);
    Layout* layout = game->getLayout();
    wallPainter = new WallItem(layout->getWalls(),cellSize,Qt::blue,cellSize/10);

    getFoodMap(layout->getFood());
    getCapsuleMap(layout->getCapsules());
    pacman = new PacmanItem(layout->getPacmanPosition(),cellSize);
    std::vector<QPointF> agentPositions = layout->getAgentsPositions();
    for(int i = 0; i< agentPositions.size();++i){
        GhostItem* ghost = new GhostItem(agentPositions[i],cellSize);
        scene()->addItem(ghost);
        ghosts.push_back(ghost);
    }
    scene()->addItem(pacman);
    scene()->addItem(wallPainter);
    for (auto iter = foodMap.begin();iter!=foodMap.end();++iter){
       scene()->addItem(iter->second);
    }
    for(auto iter = capsuleMap.begin();iter!=capsuleMap.end();++iter){
        scene()->addItem(iter->second);
    }
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(gameLoop()));
    timer->start(10);
}

void Canvas::drawState(GameState *state)

{
    if(state->isWin() || state->isLose()){
        timer->stop();
    }

    QPointF pos = state->getAgentPosition(0);
    //qDebug() << '(' << pos.y() << ',' <<pos.x() << ')';
    pacman->setRect(QRectF(pos.y()*cellSize,pos.x()*cellSize,cellSize,cellSize));
    for(int i = 0;i<ghosts.size();++i){
        GhostItem* currentGhost = ghosts[i];
        QPointF ghostPos = state->getAgentPosition(i+1);
        currentGhost->setRect(QRectF(ghostPos.y()*cellSize,ghostPos.x()*cellSize,cellSize,cellSize));
        if(state->isScared(i+1)) {
            currentGhost->setBrush(QBrush(Qt::green));
        } else {
            currentGhost->setBrush(QBrush(Qt::red));
        }
    }
    QPointF eatenFood = state->getEatenFood();
    if(foodMap.find(eatenFood)!=foodMap.end()){
        scene()->removeItem(foodMap[eatenFood]);
        delete foodMap[eatenFood];
    }
    QPointF eatenCapsule = state->getEatenCapsule();
    if(capsuleMap.find(eatenCapsule)!=capsuleMap.end()){
        scene()->removeItem(capsuleMap[eatenCapsule]);
        delete capsuleMap[eatenCapsule];
    }
}

void Canvas::gameLoop()
{

    drawState(game->step());
    scene()->update(scene()->sceneRect());
}


void Canvas::getCapsuleMap(std::vector<QPointF> caps)
{
    for(auto p:caps){
        capsuleMap[p] = new QGraphicsEllipseItem(p.y()*cellSize,p.x()*cellSize,cellSize,cellSize);
        capsuleMap[p]->setBrush(QBrush(Qt::white));
    }
}


void Canvas::getFoodMap(std::vector<std::vector<bool> > foodTable)
{
    for(int i=0;i<foodTable.size();++i){
        for(int j=0;j<foodTable[0].size();++j){
            if(foodTable[i][j]){
                QPointF p(i,j);
                foodMap[p] = new QGraphicsEllipseItem(p.y()*cellSize+cellSize/2,p.x()*cellSize+cellSize/2,cellSize/5,cellSize/5);
                foodMap[p]->setBrush(QBrush(Qt::white));

            }
        }
    }
}
