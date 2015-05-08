#ifndef SCOREMENU_H
#define SCOREMENU_H
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <vector>
#include <QPushButton>
#include <QComboBox>
#include <QSettings>
#include "engine/game.h"
#include <ui/resourceloader.h>
#include "engine/util.h"
#include "mainmenu.h"
class ScoreMenu : public QWidget
{
    Q_OBJECT
public:
    ScoreMenu(int cellSize);
    std::vector<QLabel*> learning;
    std::vector<QLabel*> minimax;
    std::vector<QLabel*> expectimax;
    std::vector<QLabel*> keyboard;
    QComboBox* layoutsList;
    QPushButton* toMenu;
public slots:
    void exitToMenu();
    void workWithLayouts(int);
private:
    QSettings *settings ;
    int cellSize;
    std::vector<int> getScores(QString agentName);
    void setAgentLabels(std::vector<int> values,std::vector<QLabel*>& agentLabs);
    void setAgent(QString agentName);
    void setCombo(QStringList layouts);
    void initLabels();
};

#endif // SCOREMENU_H
