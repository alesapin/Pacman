#include "settings.h"
#include <QDebug>

/**
 * @brief Settings::Settings
 * @param opts
 */
const int Settings::SPEED_CONVERSION = 50;
Settings::Settings(GameOptions &opts)
{
    startOptions = opts;
    delete &opts;
    setWindowTitle("Pacman");
    cellSize = opts.cellSize;
    QFont pixelFont("Munro",cellSize/1.5);
    QFont paramsFont("Munro",cellSize/2);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* pacmanLine = new QHBoxLayout();
    setStyleSheet(ResourceLoader::STYLE);
    this->setContentsMargins(cellSize*3,cellSize*3,cellSize*3,cellSize*3);
    mainLayout->setSpacing(cellSize/5.);
    pacman = new QLabel(this);
    pacman->setText("Player Agent: ");
    pacman->setFont(pixelFont);
    pacmanList = new QComboBox(this);
    pacmanList->addItem("LEARNING");
    pacmanList->addItem("MINIMAX");
    pacmanList->addItem("EXPECTIMAX");
    pacmanList->addItem("KEYBOARD");
    pacmanList->setMinimumWidth(cellSize*5);
    pacmanList->setFont(pixelFont);
    pacmanLine->addWidget(pacman);
    pacmanLine->addWidget(pacmanList);

    QHBoxLayout* ghostLine = new QHBoxLayout();
    ghost = new QLabel(this);
    ghost->setText("Ghost Agent:");
    ghost->setFont(pixelFont);
    ghostList = new QComboBox(this);
    ghostList->addItem("RUSH");
    ghostList->addItem("RANDOM");
    ghostList->addItem("DIRECTIONAL");
    ghostList->setFont(pixelFont);

    ghostLine->addWidget(ghost);
    ghostLine->addWidget(ghostList);

    QHBoxLayout* sizeLine = new QHBoxLayout();

    cells = new QLabel(this);
    cells->setText("Cells size:");
    cells->setFont(pixelFont);
    cellSizeList = new QComboBox(this);
    cellSizeList->setFont(pixelFont);
    for(int i = 10;i<=50;i+=5){
        cellSizeList->addItem(QString::number(i));
    }

    sizeLine->addWidget(cells);
    sizeLine->addWidget(cellSizeList);

    QHBoxLayout* chooseLine = new QHBoxLayout();

    chooseLevel = new QLabel(this);
    chooseLevel->setText("Level:");
    chooseLevel->setFont(pixelFont);
    chooseLevelList = new QComboBox(this);
    QDir layDir(ResourceLoader::LAYOUTS_PATH);
    layDir.setNameFilters(QStringList()<<"*.lay");
    QStringList layouts = layDir.entryList(QDir::NoDotAndDotDot|QDir::AllEntries);
    chooseLevelList->addItems(layouts);
    chooseLine->addWidget(chooseLevel);
    chooseLine->addWidget(chooseLevelList);
    chooseLevelList->setFont(pixelFont);
    learningParamsLine = new QHBoxLayout();

    alpha = new QLabel(this);
    alpha->setText("alpha:");
    epsilon = new QLabel(this);
    epsilon->setText("epsilon:");
    gamma = new QLabel(this);
    gamma->setText("gamma:");
    numiters = new QLabel(this);
    numiters->setText("Amount of iters:");
    alpha->setFont(paramsFont);
    gamma->setFont(paramsFont);
    epsilon->setFont(paramsFont);
    numiters->setFont(paramsFont);
    alphaEdit = new QLineEdit();
    alphaEdit->setMaximumWidth(40);
    epsilonEdit = new QLineEdit();
    epsilonEdit->setMaximumWidth(40);
    gammaEdit = new QLineEdit();
    gammaEdit->setMaximumWidth(40);
    numitersEdit = new QLineEdit();
    numitersEdit->setMaximumWidth(40);
    learningParamsLine->addWidget(alpha);
    learningParamsLine->addWidget(alphaEdit);
    learningParamsLine->addWidget(epsilon);
    learningParamsLine->addWidget(epsilonEdit);
    learningParamsLine->addWidget(gamma);
    learningParamsLine->addWidget(gammaEdit);
    learningParamsLine->addWidget(numiters);
    learningParamsLine->addWidget(numitersEdit);

    minimaxParamsLine = new QHBoxLayout();
    minimaxParamsLine->setAlignment(Qt::AlignCenter);
    maxDepth = new QLabel();
    maxDepth->setText("Minimax depth:");
    maxDepth->setFont(paramsFont);
    maxDepth->setMaximumWidth(cellSize*5);
    depthEdit = new QLineEdit();
    depthEdit->setMaximumWidth(40);
    gameSpeed = new QLabel("Speed:");
    gameSpeed->setFont(paramsFont);
    gameSpeed->setMaximumWidth(cellSize*2);
    gameSpeedSlide = new QSlider(Qt::Horizontal);
    gameSpeedSlide->setMaximum(4);
    gameSpeedSlide->setMinimum(1);
    gameSpeedSlide->setMaximumWidth(cellSize*5);
    minimaxParamsLine->addWidget(maxDepth);
    minimaxParamsLine->addWidget(depthEdit);
    minimaxParamsLine->addWidget(gameSpeed);
    minimaxParamsLine->addWidget(gameSpeedSlide);
    QHBoxLayout* buttonLine = new QHBoxLayout();

    saveSettings = new QPushButton(this);
    saveSettings->setText("Save");
    saveSettings->setFont(pixelFont);
    resetSettings = new QPushButton(this);
    resetSettings->setText("Reset");
    resetSettings->setFont(pixelFont);
    toMenu = new QPushButton(this);
    toMenu->setText("Menu");
    toMenu->setFont(pixelFont);
    fillFromOptions(startOptions);
    buttonLine->addWidget(saveSettings);
    buttonLine->addWidget(resetSettings);
    buttonLine->addWidget(toMenu);
    mainLayout->addLayout(pacmanLine,0);
    mainLayout->addLayout(ghostLine,1);
    mainLayout->addLayout(sizeLine,2);
    mainLayout->addLayout(chooseLine,3);
    mainLayout->addLayout(learningParamsLine,4);
    mainLayout->addLayout(minimaxParamsLine,5);
    mainLayout->addLayout(buttonLine,6);
    connect(pacmanList, SIGNAL(currentIndexChanged(int)),this,SLOT(workWithParams(int)));
    connect(saveSettings,SIGNAL(clicked()),this,SLOT(saveParams()));
    connect(toMenu,SIGNAL(clicked()),this,SLOT(startMenu()));
    connect(resetSettings,SIGNAL(clicked()),this,SLOT(resetParams()));
    setLayout(mainLayout);
    Util::center(*this);
}

void Settings::writeToFile(GameOptions &opts)
{
    QSettings *settings = new QSettings(ResourceLoader::CONFIG_PATH,QSettings::NativeFormat);
    settings->setValue("layoutPath",opts.layoutPath);
    settings->setValue("pacmanAgent",opts.pacmanAgent);
    if(opts.pacmanAgent == Game::LEARNING){
        settings->setValue("alpha",opts.alpha);
        settings->setValue("epsilon",opts.epsilon);
        settings->setValue("gamma",opts.gamma);
        settings->setValue("numIters",opts.numIters);
    }else if(!(opts.pacmanAgent == Game::KEYBOARD)){
        settings->setValue("maxDepth",opts.minimaxDepth);
    }
    settings->setValue("ghostAgent",opts.ghostAgent);
    settings->setValue("cellSize",opts.cellSize);
    settings->setValue("gameSpeed",opts.gameSpeed);
    settings->sync();
}


void Settings::workWithParams(int ind)
{
    if(ind == 0){
        swapLearnParams(true);
        swapMinimaxParams(false);
    }else if(ind !=3){
        swapLearnParams(false);
        swapMinimaxParams(true);
    }else{
        swapLearnParams(false);
        swapMinimaxParams(false);
    }
    minimaxParamsLine->update();
    learningParamsLine->update();
}

void Settings::resetParams()
{
    fillFromOptions(startOptions);
}

void Settings::saveParams()
{
   GameOptions opts;
   opts.pacmanAgent = pacmanList->currentText();
   if(opts.pacmanAgent == Game::LEARNING){

       opts.alpha = alphaEdit->text().toDouble();
       opts.epsilon = epsilonEdit->text().toDouble();
       opts.gamma = gammaEdit->text().toDouble();
       opts.numIters = numitersEdit->text().toInt();
   } else if(!(opts.pacmanAgent == Game::KEYBOARD)){
       opts.minimaxDepth = depthEdit->text().toInt();
   }
   opts.ghostAgent = ghostList->currentText();
   opts.layoutPath ="layouts/"+ chooseLevelList->currentText();
   opts.cellSize = cellSizeList->currentText().toInt();
   opts.gameSpeed = (5-gameSpeedSlide->value())*SPEED_CONVERSION;
   if(checkSettings(opts)){
        writeToFile(opts);
   }
}

void Settings::startMenu()
{
    MainMenu *m = new MainMenu();
    this->close();
    m->show();
}

void Settings::swapLearnParams(bool val)
{
    epsilonEdit->setEnabled(val);
    alphaEdit->setEnabled(val);
    gammaEdit->setEnabled(val);
    numitersEdit->setEnabled(val);
    if(!val){
        epsilonEdit->setText("");
        alphaEdit->setText("");
        gammaEdit->setText("");
        numitersEdit->setText("");
    }
}

void Settings::swapMinimaxParams(bool val)
{
    depthEdit->setEnabled(val);
    if(!val){
        depthEdit->setText("");
    }
}

void Settings::fillFromOptions(GameOptions &opts)
{
    if(opts.pacmanAgent == Game::LEARNING){
        pacmanList->setCurrentIndex(0);
    }else if(opts.pacmanAgent == Game::MINIMAX){
        pacmanList->setCurrentIndex(1);
    }else if(opts.pacmanAgent == Game::EXPECTIMAX){
        pacmanList->setCurrentIndex(2);
    }else{
        pacmanList->setCurrentIndex(3);
    }

    if(opts.ghostAgent == Game::RUSH){
        ghostList->setCurrentIndex(0);
    }else if(opts.ghostAgent == Game::RANDOM){
        ghostList->setCurrentIndex(1);
    } else{
        ghostList->setCurrentIndex(2);
    }
    cellSizeList->setCurrentIndex((opts.cellSize-10)/5);
    gameSpeedSlide->setValue(5-opts.gameSpeed/SPEED_CONVERSION);
    if(opts.pacmanAgent == Game::LEARNING){
        alphaEdit->setText(QString::number(opts.alpha,'g',2));
        epsilonEdit->setText(QString::number(opts.epsilon,'g',2));
        gammaEdit->setText(QString::number(opts.gamma,'g',2));
        numitersEdit->setText(QString::number(opts.numIters));
        depthEdit->setEnabled(false);
    }else if (!(opts.pacmanAgent == Game::KEYBOARD)){
        depthEdit->setText(QString::number(opts.minimaxDepth));
        alphaEdit->setEnabled(false);
        epsilonEdit->setEnabled(false);
        gammaEdit->setEnabled(false);
        numitersEdit->setEnabled(false);
    }else{
        depthEdit->setEnabled(false);
        alphaEdit->setEnabled(false);
        epsilonEdit->setEnabled(false);
        gammaEdit->setEnabled(false);
        numitersEdit->setEnabled(false);
    }
    QString currentLay = opts.layoutPath.split("/").value(1);
    for(int i =0;i<chooseLevelList->count();++i){
        QString lay = chooseLevelList->itemText(i);
        if(lay == currentLay){
            chooseLevelList->setCurrentIndex(i);
        }
    }
}

void Settings::alert(QString text)
{
    QMessageBox* box = new QMessageBox(this);
    box->setText(text);
    box->exec();
}

bool Settings::checkSettings(GameOptions &opts)
{
    if(opts.pacmanAgent == Game::LEARNING){
        if(opts.alpha < 0 || opts.alpha > 1){
            alert("Incorrect alpha![0..1]");
            return false;
        }
        if(opts.epsilon < 0 || opts.epsilon > 1){
            alert("Incorrect epsilon![0..1]");
            return false;
        }
        if(opts.gamma < 0 || opts.gamma > 1){
            alert("Incorrect gamma![0..1]");
            return false;
        }
        if(opts.numIters < 1){
            alert("Incorrect iters![1.. \u221e]");
            return false;
        }
    }else if (opts.pacmanAgent != Game::KEYBOARD){
        if(opts.minimaxDepth < 1 || opts.minimaxDepth > 20){
            alert("Incorrect minimax depth![1..20]");
            return false;
        }
    }
    return true;
}
