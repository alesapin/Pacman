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
private:
    QPushButton* wallMode;
    QPushButton* emptyMode;
    QPushButton* ghostMode;
    QPushButton* pacmanMode;
    QPushButton* foodMode;
    QPushButton* capsuleMode;
    QPushButton* saveToFile;
    QPushButton* exitToMenu;
    QLineEdit* layoutName;

    Field* field;
};

#endif // LEVELCREATOR_H
