#include "field.h"
#include <QDebug>

Field::Field(int w, int h, int cs):
    width(w),
    height(h),
    cellSize(cs),
    currentMode(WALL)
{

    setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);
    setCacheMode(QGraphicsView::CacheBackground);
    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setWindowTitle("Pacman");
    currentScene = new NetScene(w,h,cs);
    setScene(currentScene);
    setStyleSheet(ResourceLoader::STYLE);
    data.resize(height);
    items.resize(height);
    for(int i =0;i<height;++i){
        data[i] = std::vector<CellType>(width);
        items[i] = std::vector<QGraphicsItem*>(width);
        for(int j =0;j<width;++j){
            data[i][j] = EMPTY;
            items[i][j] = 0;
        }
    }
    drawBorder();
    drawRandomPacman();
    setGeometry(0,0,30*cellSize,30*cellSize);
    setFixedSize(30*cellSize,30*cellSize);
}
CellType Field::getCurrentMode() const
{
    return currentMode;
}

void Field::setCurrentMode(const CellType &value)
{
    currentMode = value;
}

void Field::mousePressEvent(QMouseEvent *event)
{
    QPointF cursorPos = mapToScene(QWidget::mapFromGlobal(QCursor::pos()));
    int i = (int)cursorPos.x()/cellSize;
    int j = (int)cursorPos.y()/cellSize;
    if(i!=0 && j!=0 && i != width-1 && j != height-1){
        if(event->buttons() & Qt::LeftButton){
             drawCell(i,j,currentMode);
        }else if(event->buttons() & Qt::RightButton){
            drawCell(i,j,EMPTY);
        }

    }
}

void Field::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()){
        QPointF cursorPos = mapToScene(QWidget::mapFromGlobal(QCursor::pos()));
        int i = (int)cursorPos.x()/cellSize;
        int j = (int)cursorPos.y()/cellSize;
        if(i>0 && j>0 && i < width-1 && j < height-1){
            if(event->buttons() & Qt::LeftButton){
                 drawCell(i,j,currentMode);
            }else if(event->buttons() & Qt::RightButton){
                drawCell(i,j,EMPTY);
            }
        }
    }
}

void Field::removeItem(int i, int j)
{
    if(items[j][i] != 0){
        scene()->removeItem(items[j][i]);
        delete items[j][i];
        items[j][i]=0;
        if(data[j][i] == PACMAN && currentMode != PACMAN){
            drawRandomPacman();
        }
        data[j][i] = EMPTY;
    }
}


void Field::drawWall(int i, int j)
{

    if(data[j][i] != WALL){
        removeItem(i,j);
        QGraphicsRectItem* r = new QGraphicsRectItem(i*cellSize,j*cellSize,cellSize,cellSize);
        r->setBrush(QBrush(Qt::blue));
        data[j][i]=WALL;
        scene()->addItem(r);
        items[j][i] = r;
    }
}

void Field::drawEmpty(int i, int j)
{
    if(data[j][i]!= EMPTY){
        removeItem(i,j);
    }
}

void Field::drawPacman(int i, int j)
{
    if(data[j][i] != PACMAN){
        removeItem(i,j);
        QPoint old =getPacmanPos();
        if(old.x() != -1 ){
            removeItem(old.x(),old.y());
        }
        QGraphicsEllipseItem* p = new QGraphicsEllipseItem(i*cellSize+cellSize/6,j*cellSize+cellSize/6,cellSize/1.5,cellSize/1.5);
        p->setBrush(QBrush(Qt::yellow));
        data[j][i]=PACMAN;
        scene()->addItem(p);
        items[j][i] = p;
    }
}

void Field::drawFood(int i, int j)
{
    if(data[j][i]!=FOOD){
        removeItem(i,j);
        QGraphicsEllipseItem* f = new QGraphicsEllipseItem(i*cellSize+cellSize/2.5,j*cellSize+cellSize/2.5,cellSize/5,cellSize/5);
        f->setBrush(QBrush(Qt::white));
        data[j][i] = FOOD;
        scene()->addItem(f);
        items[j][i] = f;
    }
}

void Field::drawGhost(int i, int j)
{
    if(data[j][i]!=GHOST){
       removeItem(i,j);
       if(countGhosts() >= 4 ){
           removeRandomGhost();
       }
       QGraphicsRectItem* g = new QGraphicsRectItem(i*cellSize+cellSize/4,j*cellSize+cellSize/4,cellSize/2,cellSize/2);
       g->setBrush(QBrush(Qt::red));
       data[j][i] = GHOST;
       scene()->addItem(g);
       items[j][i] = g;
    }
}

void Field::drawCapsule(int i, int j)
{
    if (data[j][i]!=CAPSULE) {
        removeItem(i,j);
        QGraphicsEllipseItem* c  = new QGraphicsEllipseItem(i*cellSize+cellSize/4,j*cellSize+cellSize/4,cellSize/2,cellSize/2);
        c->setBrush(QBrush(Qt::white));
        data[j][i]=CAPSULE;
        scene()->addItem(c);
        items[j][i] = c;
    }
}

void Field::drawCell(int i, int j, CellType type)
{
    switch(type){
    case WALL:
        drawWall(i,j);
        break;
    case EMPTY:
        drawEmpty(i,j);
        break;
    case FOOD:
        drawFood(i,j);
        break;
    case CAPSULE:
        drawCapsule(i,j);
        break;
    case GHOST:
        drawGhost(i,j);
        break;
    case PACMAN:
        drawPacman(i,j);
        break;
    }
}

void Field::drawRandomPacman()
{
    int i = rand()%height;
    int j = rand()%width;
    if(hasEmpty()){
        while(data[i][j]!=EMPTY){
            i = rand()%height;
            j = rand()%width;
        }
    }else{
        while(i==0 || j==0 || j == width-1 || i == height-1){
            i = rand()%height;
            j = rand()%width;
        }
    }
    drawPacman(j,i);
}

QPoint Field::getPacmanPos()
{
    for(int i = 0; i<height ;++i){
        for(int j = 0; j<width; ++j){
            if(data[i][j] == PACMAN){
                return QPoint(j,i);
            }
        }
    }
    return QPoint(-1,-1);
}

bool Field::hasEmpty()
{
    for(int i = 0; i<height ;++i){
        for(int j = 0; j<width; ++j){
            if(data[i][j] == EMPTY){
                return true;
            }
        }
    }
    return false;
}

bool Field::hasPacman()
{
    for(int i = 0; i<height ;++i){
        for(int j = 0; j<width; ++j){
            if(data[i][j] == PACMAN){
                return true;
            }
        }
    }
    return false;
}

int Field::countGhosts()
{
    int counter = 0;
    for(int i = 0; i<height ;++i){
        for(int j = 0; j<width; ++j){
            if(data[i][j] == GHOST){
                counter++;
            }
        }
    }
    return counter;
}

void Field::removeRandomGhost()
{
    std::vector<QPoint> ghosts;
    for(int i = 0; i<height ;++i){
        for(int j = 0; j<width; ++j){
            if(data[i][j] == GHOST){
                ghosts.push_back(QPoint(j,i));
            }
        }
    }
    int ind = rand() % ghosts.size();
    removeItem(ghosts[ind].x(),ghosts[ind].y());
}

void Field::drawBorder()
{
    for(int i =0;i<width;++i){
        for(int j = 0;j<height;++j){
            if(i==0 || j==0 || i == width-1 || j== height-1){
                drawWall(i,j);
            }
        }
    }
}

QString Field::dataToString()
{
    QString result;
    for(int i =0;i<height;++i){
        for(int j = 0 ; j< width;++j){
            result +=converToSym(data[i][j]);
        }
        result+='\n';
    }
    return result;
}

void Field::stringToFile(QString name, QString data)
{
    QFile file(ResourceLoader::LAYOUTS_PATH+"/"+name);
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream out(&file);
    out << data;
    file.close();
}

void Field::toFile(QString fileName)
{
    stringToFile(fileName,dataToString());
}

void Field::resize(int w, int h, int cs)
{
    width = w;
    height = h;
    cellSize = cs;
    currentScene->setSceneRect(0,0,w*cellSize,h*cellSize);
    currentScene->setCellSize(cellSize);
    currentScene->setWidth(width);
    currentScene->setHeight(height);
    for(int i = 0;i<data.size();++i){
        for(int j = 0;j<data[0].size();++j){
            if((i==0 || j==0 || i==data.size()-1 || j == data[0].size()-1 || j>=width-1 || i>=height-1) && data[i][j]!=EMPTY){
                data[i][j]=EMPTY;
                scene()->removeItem(items[i][j]);
                delete items[i][j];
                items[i][j]=0;
            }
        }
    }
    data.resize(h);
    items.resize(h);
    for(int i = 0; i<h;++i){
        data[i].resize(w);
        items[i].resize(w);

    }
    drawBorder();
    if(!hasPacman()){
        drawRandomPacman();
    }
    currentScene->update(currentScene->sceneRect());
}

QChar Field::converToSym(CellType t)
{
    switch (t) {
    case WALL:
        return '%';
    case PACMAN:
        return 'P';
    case GHOST:
        return 'G';
    case FOOD:
        return '.';
    case CAPSULE:
        return 'o';
    default:
        return ' ';
    }
}
