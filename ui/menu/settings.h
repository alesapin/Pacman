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
#include <QSlider>
#include "mainmenu.h"
#include <QMessageBox>
#include <QCheckBox>
class Settings: public QWidget
{
    Q_OBJECT
public:
    Settings(GameOptions& opts);
    static void generateDefaultConfig();
    void writeToFile(GameOptions& opts);
    const static int SPEED_CONVERSION;
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
    QLabel* gameSpeed;
    QLabel* sound;
    QComboBox* pacmanList;
    QComboBox* ghostList;
    QComboBox* cellSizeList;
    QComboBox* chooseLevelList;
    QCheckBox* soundChecker;
    QLineEdit* alphaEdit;
    QLineEdit* epsilonEdit;
    QLineEdit* gammaEdit;
    QLineEdit* numitersEdit;
    QLineEdit* depthEdit;
    QSlider* gameSpeedSlide;
    QHBoxLayout* minimaxParamsLine;
    QHBoxLayout* learningParamsLine;
    int cellSize;
    void swapLearnParams(bool);
    void swapMinimaxParams(bool);
    GameOptions startOptions;
    void fillFromOptions(GameOptions&);
    void alert(QString text);
    bool checkSettings(GameOptions& opts);
};

#endif // SETTINGS_H
