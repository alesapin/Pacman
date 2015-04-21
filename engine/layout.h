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
    Layout(QString path);
    Layout(const Layout& l);
    Layout();
    bool isWall(QPointF point) const;
    QPointF getRandomLegalPosition() const;
    void processLayoutChar(int i,int j,QChar character);
    void processLayoutText(QString text);
    const std::vector <std::vector <bool> >& getWalls() const;
    std::vector <std::vector <bool> > getFood() const;
    int getTotalFood() const;
    std::vector <QPointF> getCapsules() const;
    std::vector <QPointF> getAgentsPositions() const;
    QPointF getPacmanPosition() const;
private:
    int width;
    int height;
    int totalFood;
    int numAgents;
    std::vector<std::vector <bool> > walls;
    std::vector<std::vector <bool> > food;
    std::vector<QPointF> capsules;
    std::vector<QPointF> agentsPositions;
    QString layoutText;
};

#endif // LAYOUT_H
