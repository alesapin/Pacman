#include "levelcreator.h"




LevelCreator::LevelCreator(int w,int h,int cellSize,QWidget *parent):
    QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);

    setStyleSheet(ResourceLoader::STYLE);
    QHBoxLayout* fieldLayout = new QHBoxLayout();
    fieldLayout->setAlignment(Qt::AlignCenter);
    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->setAlignment(Qt::AlignCenter);
    QHBoxLayout* headerLayout = new QHBoxLayout();
    headerLayout->setAlignment(Qt::AlignRight);
    field = new Field(w,h,cellSize);
    fieldLayout->addWidget(field);
    wallMode = new QPushButton("Wall");
    emptyMode = new QPushButton("Empt");
    ghostMode = new QPushButton("Ghst");
    pacmanMode = new QPushButton("Pcmn");
    foodMode = new QPushButton("Food");
    capsuleMode = new QPushButton("Cpsl");
    saveToFile = new QPushButton("Save");
    exitToMenu = new QPushButton("Menu");
    layoutName = new QLineEdit();
    layoutName->setMinimumWidth(cellSize*3);
    headerLayout->addWidget(saveToFile);
    headerLayout->addWidget(layoutName);
    headerLayout->addWidget(exitToMenu);
    buttonsLayout->addWidget(wallMode);
    buttonsLayout->addWidget(emptyMode);
    buttonsLayout->addWidget(ghostMode);
    buttonsLayout->addWidget(pacmanMode);
    buttonsLayout->addWidget(foodMode);
    buttonsLayout->addWidget(capsuleMode);
    mainLayout->addLayout(headerLayout);
    mainLayout->addLayout(fieldLayout);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);
    connect(wallMode,SIGNAL(clicked()),this,SLOT(wallSignal()));
    connect(emptyMode,SIGNAL(clicked()),this,SLOT(emptySignal()));
    connect(ghostMode,SIGNAL(clicked()),this,SLOT(ghostSignal()));
    connect(pacmanMode,SIGNAL(clicked()),this,SLOT(pacmanSignal()));
    connect(foodMode,SIGNAL(clicked()),this,SLOT(foodSignal()));
    connect(capsuleMode,SIGNAL(clicked()),this,SLOT(capsuleSignal()));
    connect(saveToFile,SIGNAL(clicked()),this,SLOT(save()));
    connect(exitToMenu,SIGNAL(clicked()),this,SLOT(toMenu()));
    setGeometry(0,0,(w+3)*cellSize,(h+3)*cellSize);
    Util::center(*this);

}

void LevelCreator::wallSignal()
{
    field->setCurrentMode(WALL);
}

void LevelCreator::emptySignal()
{
    field->setCurrentMode(EMPTY);
}

void LevelCreator::ghostSignal()
{
    field->setCurrentMode(GHOST);
}

void LevelCreator::pacmanSignal()
{
    field->setCurrentMode(PACMAN);
}

void LevelCreator::foodSignal()
{
    field->setCurrentMode(FOOD);
}

void LevelCreator::capsuleSignal()
{
    field->setCurrentMode(CAPSULE);
}

void LevelCreator::save()
{
    QString fileName = layoutName->text();
    if(!fileName.endsWith(".lay")){
        fileName+=".lay";
    }
    field->toFile(fileName);
}

void LevelCreator::toMenu()
{
    MainMenu *m = new MainMenu();
    this->close();
    m->show();
}
