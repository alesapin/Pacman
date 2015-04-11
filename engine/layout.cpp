#include "layout.h"
#include <fstream>
#include <QDebug>

/**
 * @brief Layout::Layout
 * @param path
 * @param cellSize
 */
Layout::Layout(std::string path):
    totalFood(0),
    numAgents(0)
{
    std::ifstream file(path);
    std::string tmp;
    width = 0;
    while (std::getline(file, tmp))
    {
        width+=1;
        layoutText += tmp;
        qDebug() << layoutText.c_str();
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
void Layout::processLayoutChar(int i, int j, char character)
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
        pacmanPosition = QPointF(i,j);
        numAgents++;
    }else if (character == 'G'){
        agentsPositions.push_back(QPointF(i,j));
        numAgents++;
    }
}

void Layout::processLayoutText(std::string text)
{
    for(int i=0;i<width;++i){
        for(int j =0;j<height;++j){
            char currentChar= text[i*height + j];
            processLayoutChar(i,j,currentChar);
        }
    }
}

const std::vector<std::vector<bool> >& Layout::getWalls()
{
    return walls;
}

std::vector<std::vector<bool> > Layout::getFood()
{
    return food;
}

std::vector<QPointF> Layout::getCapsules()
{
    return capsules;
}

std::vector<QPointF> Layout::getAgentsPositions()
{
    return agentsPositions;
}

QPointF Layout::getPacmanPosition()
{
    return pacmanPosition;
}

