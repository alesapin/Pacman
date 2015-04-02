#include "canvas.h"
#include <QDebug>

Canvas::Canvas(Layout* lay)
{
    setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);
        setCacheMode(QGraphicsView::CacheNone);
//    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    myScene = new QGraphicsScene();
    this->setStyleSheet("background-color: black;");
    setScene(myScene);
    this->layout = lay;
    currentGameState = GameState(*lay);
    wallPainter = new WallItem(layout->getWalls(),layout->getCellSize(),Qt::blue,layout->getCellSize()/10);
    cellSize = layout->getCellSize();
    getFoodMap(layout->getFood());
    getCapsuleMap();
    ReflectAgent* ref = new ReflectAgent();
    pacman = new PacmanKeyboardItem(lay->getPacmanPosition(),layout->getCellSize());
    std::vector<QPointF> agentPositions = lay->getAgentsPositions();
    for(int i = 0;i< agentPositions.size();++i){
        RandomGhostAgent* agent = new RandomGhostAgent(i+1);

        GhostItem* ghost = new GhostItem(*agent,agentPositions[i],layout->getCellSize());
        scene()->addItem(ghost);
        ghosts.push_back(ghost);
    }
    scene()->addItem(pacman);
    scene()->addItem(wallPainter);
    //pacman->setParentItem(wallPainter);
    for (auto iter = foodMap.begin();iter!=foodMap.end();++iter){
       scene()->addItem(iter->second);
    }
    for(auto iter = capsuleMap.begin();iter!=capsuleMap.end();++iter){
        scene()->addItem(iter->second);
    }
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(gameLoop()));
    timer->start(10);
    currentMover = 0;
}


void Canvas::drawMoving()
{
    if(currentMover == 0) {

        currentGameState = currentGameState.generatePacmanSuccessor(pacman->getAction(currentGameState));
        if(currentGameState.isWin() || currentGameState.isLose()) timer->stop();
        QPointF pos = currentGameState.getPacmanPosition();
        pacman->setRect(QRectF(pos.y()*cellSize,pos.x()*cellSize,cellSize,cellSize));
        QPointF eaten =currentGameState.getEatenFood();
        if(foodMap.find(eaten)!=foodMap.end()){
            scene()->removeItem(foodMap[eaten]);
        }
        QPointF eatenCapsule = currentGameState.getEatenCapsule();
        if(capsuleMap.find(eatenCapsule)!=capsuleMap.end()){
            scene()->removeItem(capsuleMap[eatenCapsule]);
        }
    }else{
        GhostItem* ghost = ghosts[currentMover-1];

        currentGameState = currentGameState.generateSuccessor(currentMover,ghost->getAction(currentGameState));
        if(currentGameState.isWin() || currentGameState.isLose()) timer->stop();
        QPointF pos = currentGameState.getGhostState(currentMover).getPosition();
       // qDebug() << pos.x() << " "<<pos.y();
        if(currentGameState.isScared(currentMover)) {
            ghost->setBrush(QBrush(Qt::green));
        } else {
            ghost->setBrush(QBrush(Qt::red));
        }

        ghost->setRect(QRectF(pos.y()*cellSize,pos.x()*cellSize,cellSize,cellSize));
    }
    currentMover = (currentMover+1)%(ghosts.size()+1);
    //qDebug() << "Score:"<<currentGameState.getScore();

}

void Canvas::gameLoop()
{

    drawMoving();
    scene()->update(scene()->sceneRect());
}

void Canvas::drawGhosts()
{

}

void Canvas::getCapsuleMap()
{
    for(auto p:currentGameState.getCapsules()){
        capsuleMap[p] = new QGraphicsEllipseItem(p.y()*cellSize,p.x()*cellSize,cellSize,cellSize);
        capsuleMap[p]->setBrush(* new QBrush(Qt::white));
    }
}


void Canvas::getFoodMap(std::vector<std::vector<bool> > foodTable)
{
    for(int i=0;i<foodTable.size();++i){
        for(int j=0;j<foodTable[0].size();++j){
            if(foodTable[i][j]){
                QPointF p(i,j);
                foodMap[p] = new QGraphicsEllipseItem(p.y()*cellSize+cellSize/2,p.x()*cellSize+cellSize/2,cellSize/5,cellSize/5);
                foodMap[p]->setBrush(* new QBrush(Qt::white));

            }
        }
    }
}
