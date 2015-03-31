#include "canvas.h"
#include <QDebug>

Canvas::Canvas(Layout* lay)
{
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setRenderHint(QPainter::Antialiasing);
    myScene = new QGraphicsScene();
    this->setStyleSheet("background-color: black;");
    setScene(myScene);
    this->layout = lay;
    currentGameState = GameState(*lay);
    wallPainter = new WallItem(layout->getWalls(),layout->getCellSize(),Qt::blue,layout->getCellSize()/10);
    cellSize = layout->getCellSize();
    getFoodMap(layout->getFood());
    //ReflectAgent* ref = new ReflectAgent();
    pacman = new PacmanKeyboardItem(lay->getPacmanPosition(),layout->getCellSize());
    scene()->addItem(pacman);
    scene()->addItem(wallPainter);
    pacman->setParentItem(wallPainter);
    for (auto iter = foodMap.begin();iter!=foodMap.end();++iter){
       scene()->addItem(iter->second);
    }

    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(gameLoop()));
    timer->start(30);
}


void Canvas::drawMoving()
{
    currentGameState = currentGameState.generatePacmanSuccessor(pacman->getAction(currentGameState));
    qDebug() << "Score:"<<currentGameState.getScore();
    if(currentGameState.isWin() || currentGameState.isLose()) timer->stop();
    QPointF pos = currentGameState.getPacmanPosition();
    pacman->setRect(QRectF(pos.y()*cellSize,pos.x()*cellSize,cellSize,cellSize));
    QPointF eaten =currentGameState.getEaten();
    if(foodMap.find(eaten)!=foodMap.end()){
        scene()->removeItem(foodMap[eaten]);
    }
}

void Canvas::gameLoop()
{

    drawMoving();
    scene()->update(scene()->sceneRect());
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
