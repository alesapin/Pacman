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
    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setWindowTitle("Pacman");
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
    agentTime = opts.gameSpeed/10;
    setAgents(layout);
    generalTime = opts.gameSpeed / (ghosts.size()+1);
    setRestartButton(layout);
    setPauseButton(layout);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(gameLoop()));
    connect(restartButton,SIGNAL(clicked()),this,SLOT(restartGame()));
    connect(pauseButton,SIGNAL(clicked()),this,SLOT(pauseGame()));
    setSounds();
    layoutName = opts.layoutPath.split("/").value(1);
    agentName = opts.pacmanAgent;
    delete &opts;
    if(game->isLearning()){
        setEnabled(false);
        TrainingWindow* train = new TrainingWindow(game,this);
        train->show();
        train->raise();
        train->activateWindow();
    }else{
        startSound->stop();
        startSound->play();
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
    if(state->isWin()){
        winSound->play();
    }
    if(state->isLose()){
        loseSound->play();
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
        if(!wakaSound->isPlaying()){
            wakaSound->play();
        }
    }
    QPointF eatenCapsule = state->getEatenCapsule();
    if(capsuleMap.find(eatenCapsule)!=capsuleMap.end()){
        scene()->removeItem(capsuleMap[eatenCapsule]);
        delete capsuleMap[eatenCapsule];
        capsuleMap.erase(eatenCapsule);
        if(!eatCapsuleSound->isPlaying()){
            eatCapsuleSound->play();
        }
    }
    scoreText->updateScore(state->getScore());
}

void Canvas::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape){
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
    startSound->stop();
    startSound->play();
    timer->start(generalTime);
}


void Canvas::gameLoop()
{
    drawState(game->step());
    if(gameOver){
        this->setEnabled(false);
        GameOverMenu* go = new GameOverMenu(this);
        go->show();
        saveScore();
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
    startSound->stop();
    startSound->play();
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
    restartButton = new QPushButton();
    restartButton->setObjectName("restartButton");
    restartButton->setText("restart");
    restartButton->setStyleSheet(ResourceLoader::STYLE);
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
    pauseButton = new QPushButton();
    pauseButton->setObjectName("pauseButton");
    pauseButton->setText("pause");
    pauseButton->setStyleSheet(ResourceLoader::STYLE);
    double fontSize = width > cellSize? cellSize/1.5:width;
    pauseButton->setFont(QFont(ResourceLoader::FONT_NAME,fontSize));
    pauseButton->setFocusPolicy(Qt::NoFocus);
    QPointF buttonPos = countRestartRect(layout);
    pauseButton->setGeometry(buttonPos.x()+width*cellSize/3.,buttonPos.y(),cellSize/5,cellSize);
    pauseButton->setMinimumWidth((width*cellSize)/6.);
    pauseButton->setMaximumWidth((width*cellSize)/3.);
    scene()->addWidget(pauseButton);
}

void Canvas::saveScore()
{
    QSettings *settings = new QSettings(ResourceLoader::SCORE_LIST_PATH,QSettings::NativeFormat);
    settings->beginGroup(layoutName+"/"+agentName);
    int currentScore = scoreText->getScore();
    QStringList keys = settings->childKeys();
    if(keys.isEmpty()){
        settings->setValue("1",currentScore);
        return;
    }
    std::vector<int> values;
    for(int i = 0;i<keys.size();++i){
        values.push_back(settings->value(keys.value(i)).toInt());
    }
    values.push_back(currentScore);
    std::sort(values.begin(),values.end(),std::greater<int>());
    while (values.size() > 10) {
        values.pop_back();
    }
    for(int i=1;i<=values.size();++i){
        settings->setValue(QString::number(i),values[i-1]);
    }
}

void Canvas::setSounds()
{
    startSound = new QSoundEffect();
    wakaSound = new QSoundEffect();
    eatGhostSound = new QSoundEffect();
    eatCapsuleSound = new QSoundEffect();
    winSound = new QSoundEffect();
    loseSound = new QSoundEffect();
    startSound->setSource(QUrl(ResourceLoader::START_SOUND_PATH));
    wakaSound->setSource(QUrl(ResourceLoader::EAT_FOOD_SOUND_PATH));
    eatGhostSound->setSource(QUrl(ResourceLoader::EAT_GHOST_SOUND_PATH));
    eatCapsuleSound->setSource(QUrl(ResourceLoader::EAT_CAPS_SOUND_PATH));
    winSound->setSource(QUrl(ResourceLoader::WIN_SOUND_PATH));
    loseSound->setSource(QUrl(ResourceLoader::LOSE_SOUND_PATH));
}
