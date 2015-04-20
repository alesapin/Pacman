#include "layout.h"
#include <fstream>
#include <QDebug>
#include <QFile>
/**
 * @brief Layout::Layout
 * @param path
 * @param cellSize
 */
Layout::Layout(QString path):
    totalFood(0),
    numAgents(0)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QString tmp;
    width = 0;
    while ((tmp = in.readLine()).count())
    {
        width+=1;
        layoutText+=tmp;
        qDebug() << layoutText;
        layoutText.push_back('\n');
    }
    height= layoutText.size() / width ;
    qDebug() << "width:"<< width;
    qDebug() <<"height:"<<height;
    walls.resize(width);
    food.resize(width);
    for (int i = 0;i<walls.size();++i){
        walls[i] = std::vector<bool>(height);
        food[i] = std::vector<bool>(height);
    }
    processLayoutText(layoutText);
}

Layout::Layout(const Layout& l)
{
    totalFood = l.totalFood;
    numAgents = l.numAgents;
    walls = std::vector<std::vector<bool > >(l.walls);
    food = std::vector<std::vector<bool> >(l.food);
    width = l.width;
    height = l.height;
}

Layout::Layout():
    width(0),
    height(0),
    totalFood(0),
    numAgents(0)
{

}


/**
 * @brief Layout::processLayoutChar
 * @param i
 * @param j
 * @param character
 */
void Layout::processLayoutChar(int i, int j, QChar character)
{
   //qDebug() << "CHAR:"<< character << '\n';
    if (character == '%'){
        walls[i][j]=true;
    }else if (character == '.'){
        food[i][j]=true;
        totalFood+=1;
    }else if(character == 'o'){
        capsules.push_back(QPointF(i,j));
    }else if(character == 'P'){
        agentsPositions.insert(agentsPositions.begin(),QPointF(i,j));
        numAgents++;
    }else if (character == 'G'){
        agentsPositions.push_back(QPointF(i,j));
        numAgents++;
    }
}

void Layout::processLayoutText(QString text)
{
    for(int i=0;i<width;++i){
        for(int j =0;j<height;++j){
            QChar currentChar= text[i*height + j];
            processLayoutChar(i,j,currentChar);
        }
    }
}

const std::vector<std::vector<bool> >& Layout::getWalls() const
{
    return walls;
}

std::vector<std::vector<bool> > Layout::getFood() const
{
    return food;
}

std::vector<QPointF> Layout::getCapsules() const
{
    return capsules;
}

std::vector<QPointF> Layout::getAgentsPositions() const
{
    return agentsPositions;
}

QPointF Layout::getPacmanPosition() const
{
    return agentsPositions[0];
}

