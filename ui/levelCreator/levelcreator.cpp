#include "levelcreator.h"



const int LevelCreator::MIN_FIELD_HEIGHT = 5;
const int LevelCreator::MAX_FIELD_HEIGHT = 30;
const int LevelCreator::MIN_FIELD_WIDTH = 5;
const int LevelCreator::MAX_FIELD_WIDTH = 30;
LevelCreator::LevelCreator(int w,int h,int cellSize,QWidget *parent):
    QWidget(parent),
    cellSize(cellSize)
{


    QGridLayout* mainLayout = new QGridLayout();


    setStyleSheet(ResourceLoader::STYLE);

    field = new Field(w,h,cellSize);


    mainLayout->addWidget(field,0,0);
    mainLayout->addLayout(setLeftPanel(cellSize),0,1);
    mainLayout->addLayout(setButtonPanel(cellSize),1,0);

    setLayout(mainLayout);
    connect(wallMode,SIGNAL(clicked()),this,SLOT(wallSignal()));
    connect(emptyMode,SIGNAL(clicked()),this,SLOT(emptySignal()));
    connect(ghostMode,SIGNAL(clicked()),this,SLOT(ghostSignal()));
    connect(pacmanMode,SIGNAL(clicked()),this,SLOT(pacmanSignal()));
    connect(foodMode,SIGNAL(clicked()),this,SLOT(foodSignal()));
    connect(capsuleMode,SIGNAL(clicked()),this,SLOT(capsuleSignal()));
    connect(saveToFile,SIGNAL(clicked()),this,SLOT(save()));
    connect(exitToMenu,SIGNAL(clicked()),this,SLOT(toMenu()));
    connect(resizeField,SIGNAL(clicked()),this,SLOT(resizeF()));
    connect(widthSlider,SIGNAL(valueChanged(int)),this,SLOT(widthChanged(int)));
    connect(heightSlider,SIGNAL(valueChanged(int)),this,SLOT(heightChanged(int)));
    connect(openFile,SIGNAL(clicked()),this,SLOT(openSignal()));
    setGeometry(0,0,(40)*cellSize,(35)*cellSize);
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

void LevelCreator::openSignal()
{
    QString fileName =  QFileDialog::getOpenFileName(this,tr("Open File"),QDir::currentPath() + "/layouts",tr("Layout files (*.lay)\n"));
    qDebug() << fileName;
    QStringList name=fileName.split("/");
    layoutName->setText(name.last());
    loadFromFile(fileName);
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

void LevelCreator::resizeF()
{
    field->resize(widthSlider->value(),heightSlider->value(),cellSize);
    this->update();
}

void LevelCreator::widthChanged(int i)
{
    currentWidth->setText("W: "+QString::number(i));
}

void LevelCreator::heightChanged(int i)
{
    currentHeight->setText("H: "+QString::number(i));
}

QHBoxLayout *LevelCreator::setButtonPanel(int cellSize)
{
    wallMode = new QPushButton();
    setButtonIcon(wallMode,":/icons/icons/wallicon.png",cellSize);
    emptyMode = new QPushButton();
    setButtonIcon(emptyMode,":/icons/icons/empticon.png" ,cellSize);
    ghostMode = new QPushButton();
    setButtonIcon(ghostMode,":/icons/icons/red-icon.png" ,cellSize);

    pacmanMode = new QPushButton();
    setButtonIcon(pacmanMode,":/icons/icons/pcmnicon.png" ,cellSize);

    foodMode = new QPushButton();
    setButtonIcon(foodMode,":/icons/icons/foodicon.png" ,cellSize);

    capsuleMode = new QPushButton();
    setButtonIcon(capsuleMode,":/icons/icons/capsicon.png" ,cellSize);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(wallMode);
    buttonLayout->addWidget(emptyMode);
    buttonLayout->addWidget(ghostMode);
    buttonLayout->addWidget(pacmanMode);
    buttonLayout->addWidget(foodMode);
    buttonLayout->addWidget(capsuleMode);
    buttonLayout->setAlignment(Qt::AlignCenter);
    return buttonLayout;
}

QVBoxLayout *LevelCreator::setLeftPanel(int cellSize)
{
    QVBoxLayout* leftPanel = new QVBoxLayout();
    saveToFile = new QPushButton("Save");
    saveToFile->setMaximumWidth(cellSize*5);
    saveToFile->setFont(QFont(ResourceLoader::FONT_NAME,cellSize/1.5));

    exitToMenu = new QPushButton("Menu");
    exitToMenu->setMaximumWidth(cellSize*7);
    exitToMenu->setMinimumWidth(cellSize*5);
    exitToMenu->setFont(QFont(ResourceLoader::FONT_NAME,cellSize/1.5));
    layoutName = new QLineEdit();
    layoutName->setMinimumWidth(cellSize*3);
    layoutName->setMaximumWidth(cellSize*7);
    resizeField = new QPushButton("Resize");
    resizeField->setFont(QFont(ResourceLoader::FONT_NAME,cellSize/1.5));
    resizeField->setMaximumWidth(cellSize*7);
    widthSlider = new QSlider();
    widthSlider->setMaximum(MAX_FIELD_WIDTH);
    widthSlider->setMinimum(MIN_FIELD_WIDTH);
    widthSlider->setTickInterval(1);
    widthSlider->setMaximumWidth(cellSize*5);
    widthSlider->setOrientation(Qt::Horizontal);
    widthSlider->setValue(15);
    heightSlider = new QSlider();
    heightSlider->setMaximum(MAX_FIELD_HEIGHT);
    heightSlider->setMinimum(MIN_FIELD_HEIGHT);
    heightSlider->setTickInterval(1);
    heightSlider->setMaximumWidth(cellSize*5);
    heightSlider->setOrientation(Qt::Horizontal);
    heightSlider->setValue(15);
    openFile = new QPushButton("Open Layout");
    openFile->setMaximumWidth(cellSize*7);
    openFile->setMinimumWidth(cellSize*3);
    openFile->setFont(QFont(ResourceLoader::FONT_NAME,cellSize/1.5));
    QHBoxLayout* widthLine = new QHBoxLayout();
    QHBoxLayout* heightLine=new QHBoxLayout();
    QHBoxLayout* currentValues = new QHBoxLayout();
    QHBoxLayout* forResizeButton = new QHBoxLayout();

    QHBoxLayout* forMenuButton = new QHBoxLayout();
    QHBoxLayout* forOpenButton = new QHBoxLayout();
    QHBoxLayout* saveLine =new QHBoxLayout();

    leftPanel->setAlignment(Qt::AlignCenter);
    forMenuButton->setAlignment(Qt::AlignCenter);
    currentWidth = new QLabel("W: 15");
    currentHeight = new QLabel("H: 15");
    currentWidth->setFont(QFont(ResourceLoader::FONT_NAME,cellSize/1.5));
    currentHeight->setFont(QFont(ResourceLoader::FONT_NAME,cellSize/1.5));
    currentWidth->setMaximumWidth(cellSize*6);
    currentHeight->setMaximumWidth(cellSize*6);
    currentValues->setAlignment(Qt::AlignCenter);
    currentValues->addWidget(currentWidth);
    currentValues->addWidget(currentHeight);
    QLabel* widthLabel = new QLabel("Width: ");
    widthLabel->setFont(QFont(ResourceLoader::FONT_NAME,cellSize/1.5));
    widthLabel->setMaximumWidth(cellSize*6);
    widthLine->addWidget(widthLabel);
    widthLine->addWidget(widthSlider);
    QLabel* heightLabel = new QLabel("Height: ");
    heightLabel->setFont(QFont(ResourceLoader::FONT_NAME,cellSize/1.5));
    heightLabel->setMaximumWidth(cellSize*6);
    heightLine->addWidget(heightLabel);
    heightLine->addWidget(heightSlider);
    saveLine->addWidget(saveToFile);
    saveLine->addWidget(layoutName);
    saveLine->setAlignment(Qt::AlignCenter);
    saveLine->setContentsMargins(0,0,0,cellSize);
    leftPanel->addLayout(widthLine);
    leftPanel->addLayout(heightLine);
    leftPanel->addLayout(currentValues);
    forResizeButton->addWidget(resizeField);
    forResizeButton->setContentsMargins(0,0,0,cellSize*20);
    leftPanel->addLayout(forResizeButton);
    forOpenButton->setContentsMargins(0,0,0,cellSize);
    forOpenButton->addWidget(openFile);
    leftPanel->addLayout(forOpenButton);
    leftPanel->addLayout(saveLine);
    forMenuButton->addWidget(exitToMenu);
    leftPanel->addLayout(forMenuButton);
    return leftPanel;
}

void LevelCreator::setButtonIcon(QPushButton *button, QString texturePath,int cellSize)
{
    QPixmap texture(texturePath);
    QPixmap scaled = texture.scaledToHeight(cellSize);
    QIcon icon(scaled);
    button->setMaximumWidth(cellSize*2);
    button->setIcon(icon);
    button->setIconSize(scaled.rect().size());
}

void LevelCreator::loadFromFile(QString path)
{
    QFile f(path);
    f.open(QFile::ReadOnly);
    QStringList layoutArray = QString(f.readAll()).split('\n');
    int h = layoutArray.length()-1;
    int w = layoutArray[0].length();
    if(field->loadFromString(layoutArray)){
        heightSlider->setValue(h);
        widthSlider->setValue(w);
    }
}
