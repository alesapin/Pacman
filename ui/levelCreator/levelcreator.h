#ifndef LEVELCREATOR_H
#define LEVELCREATOR_H
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include "field.h"
#include "ui/resourceloader.h"
#include "engine/util.h"
#include "ui/menu/mainmenu.h"
#include <QSlider>
#include <QPixmap>
#include <QIcon>
class LevelCreator : public QWidget
{
    Q_OBJECT
public:
    LevelCreator(int w,int h,int cellSize,QWidget* parent=0);
public slots:
    void wallSignal();
    void emptySignal();
    void ghostSignal();
    void pacmanSignal();
    void foodSignal();
    void capsuleSignal();
    void save();
    void toMenu();
    void resizeF();
    void widthChanged(int i);
    void heightChanged(int i);
private:
    QPushButton* wallMode;
    QPushButton* emptyMode;
    QPushButton* ghostMode;
    QPushButton* pacmanMode;
    QPushButton* foodMode;
    QPushButton* capsuleMode;
    QPushButton* saveToFile;
    QPushButton* exitToMenu;
    QPushButton* resizeField;
    QLineEdit* layoutName;
    QSlider* widthSlider;
    QSlider* heightSlider;
    QLabel* currentHeight;
    QLabel* currentWidth;
    Field* field;
    QHBoxLayout* setButtonPanel(int cellSize);
    QVBoxLayout* setLeftPanel(int cellSize);
    int cellSize;
    void setButtonIcon(QPushButton* button, QString texturePath, int cellSize);
};

#endif // LEVELCREATOR_H
