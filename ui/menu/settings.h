#ifndef SETTINGS_H
#define SETTINGS_H
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include "engine/gameoptions.h"
#include <QDir>
#include <QSettings>
#include "mainmenu.h"
class Settings: public QWidget
{
    Q_OBJECT
public:
    Settings(GameOptions& opts);
    static void generateDefaultConfig();
    static void writeToFile(GameOptions& opts);
public slots:
    void workWithParams(int);
    void resetParams();
    void saveParams();
    void startMenu();
private:
    QPushButton* saveSettings;
    QPushButton* resetSettings;
    QPushButton* toMenu;
    QLabel* pacman;
    QLabel* ghost;
    QLabel* cells;
    QLabel* chooseLevel;
    QLabel* alpha;
    QLabel* epsilon;
    QLabel* gamma;
    QLabel* numiters;
    QLabel* maxDepth;
    QComboBox* pacmanList;
    QComboBox* ghostList;
    QComboBox* cellSizeList;
    QComboBox* chooseLevelList;
    QLineEdit* alphaEdit;
    QLineEdit* epsilonEdit;
    QLineEdit* gammaEdit;
    QLineEdit* numitersEdit;
    QLineEdit* depthEdit;
    QHBoxLayout* minimaxParamsLine;
    QHBoxLayout* learningParamsLine;
    int cellSize;
    void swapLearnParams(bool);
    void swapMinimaxParams(bool);
    GameOptions startOptions;
    void fillFromOptions(GameOptions&);
};

#endif // SETTINGS_H
