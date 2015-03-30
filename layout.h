#ifndef LAYOUT_H
#define LAYOUT_H
#include <vector>
#include <QPointF>
#include <QString>
#include <QChar>
#include <string>
class Layout
{
public:
    Layout(std::string path,int cellSize);
    Layout(Layout& l);
    Layout();
    bool isWall(QPointF point);
    QPointF getRandomLegalPosition();
    void processLayoutChar(int i,int j,char character);
    void processLayoutText(std::string text);
    std::vector <std::vector <bool> >& getWalls();
    std::vector <std::vector <bool> > getFood();
    std::vector <QPointF> getCapsules();
    std::vector <QPointF> getAgentsPositions();
    QPointF getPacmanPosition();
    int getCellSize();
private:
    int width;
    int height;
    int totalFood;
    int numAgents;
    int cellSize;
    std::vector<std::vector <bool> > walls;
    std::vector<std::vector <bool> > food;
    std::vector<QPointF> capsules;
    QPointF pacmanPosition;
    std::vector<QPointF> agentsPositions;
    std::string layoutText;

};

#endif // LAYOUT_H
