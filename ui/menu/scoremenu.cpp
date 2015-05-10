#include "scoremenu.h"

ScoreMenu::ScoreMenu(int cellSize):
    cellSize(cellSize)
{

    settings = new QSettings(ResourceLoader::SCORE_LIST_PATH,QSettings::NativeFormat);


    setWindowTitle("Pacman");
    setStyleSheet(ResourceLoader::STYLE);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QHBoxLayout* listLayout = new QHBoxLayout();
    buttonLayout->setAlignment(Qt::AlignCenter);
    listLayout->setAlignment(Qt::AlignCenter);
    mainLayout->setAlignment(Qt::AlignCenter);
    QHBoxLayout* tableLayout = new QHBoxLayout();
    QVBoxLayout* learningLayout = new QVBoxLayout();
    QVBoxLayout* minimaxLayout = new QVBoxLayout();
    QVBoxLayout* expectimaxLayout = new QVBoxLayout();
    QVBoxLayout* keyboardLayout = new QVBoxLayout();
    QLabel* learningTitle = new QLabel(this);
    QLabel* minimaxTitle = new QLabel(this);
    QLabel* expectimaxTitle = new QLabel(this);
    QLabel* keyboardTitle = new QLabel(this);
    learningTitle->setText("Learning Agent");
    minimaxTitle->setText("Minimax Agent");
    expectimaxTitle->setText("Expectimax Agent");
    keyboardTitle->setText("Keyboard Agent");
    learningTitle->setFont(QFont(ResourceLoader::FONT_NAME,cellSize/2));
    minimaxTitle->setFont(QFont(ResourceLoader::FONT_NAME,cellSize/2));
    expectimaxTitle->setFont(QFont(ResourceLoader::FONT_NAME,cellSize/2));
    keyboardTitle->setFont(QFont(ResourceLoader::FONT_NAME,cellSize/2));

    learningLayout->addWidget(learningTitle);
    minimaxLayout->addWidget(minimaxTitle);
    expectimaxLayout->addWidget(expectimaxTitle);
    keyboardLayout->addWidget(keyboardTitle);
    initLabels();
    setCombo(settings->childGroups());
    setAgent(Game::LEARNING);
    setAgent(Game::MINIMAX);
    setAgent(Game::EXPECTIMAX);
    setAgent(Game::KEYBOARD);
    for(int i = 0;i<10;++i){
        learningLayout->addWidget(learning[i]);
        minimaxLayout->addWidget(minimax[i]);
        expectimaxLayout->addWidget(expectimax[i]);
        keyboardLayout->addWidget(keyboard[i]);
    }
    toMenu  = new QPushButton(this);
    toMenu->setText("Menu");
    toMenu->setMaximumWidth(cellSize*9);
    toMenu->setMinimumWidth(cellSize*6);
    toMenu->setFont(QFont(ResourceLoader::FONT_NAME,cellSize/1.5));
    tableLayout->addLayout(learningLayout);
    tableLayout->addLayout(minimaxLayout);
    tableLayout->addLayout(expectimaxLayout);
    tableLayout->addLayout(keyboardLayout);
    listLayout->addWidget(layoutsList);
    mainLayout->addLayout(listLayout);
    mainLayout->addLayout(tableLayout);
    buttonLayout->addWidget(toMenu);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
    connect(toMenu,SIGNAL(clicked()),this,SLOT(exitToMenu()));
    connect(layoutsList, SIGNAL(currentIndexChanged(int)),this,SLOT(workWithLayouts(int)));
    Util::center(*this);
}

void ScoreMenu::exitToMenu()
{
    MainMenu *m = new MainMenu();
    this->close();
    m->show();
}

void ScoreMenu::workWithLayouts(int index)
{
    setAgent(Game::LEARNING);
    setAgent(Game::MINIMAX);
    setAgent(Game::EXPECTIMAX);
    setAgent(Game::KEYBOARD);
}

std::vector<int> ScoreMenu::getScores(QString agentName)
{
    QString currentLay = layoutsList->currentText();
    settings->beginGroup(currentLay+"/"+agentName);

    QStringList keys = settings->allKeys();
    std::vector<int> result;
    for(QString key:keys){
        result.push_back(settings->value(key).toInt());
    }
    settings->endGroup();
    return result;
}

void ScoreMenu::setAgentLabels(std::vector<int> values, std::vector<QLabel*>& agentLabs)
{
    for(int i = 0 ;i<10;++i){
        agentLabs[i]->setText("");
    }
    std::sort(values.begin(),values.end(),std::greater<int>());
    for(int i=0;i<values.size() && i < 10;++i){
        QLabel* lab = agentLabs[i];
        lab->setText(QString::number(i+1)+". " + QString::number(values[i]));
        lab->setFont(QFont(ResourceLoader::FONT_NAME,cellSize/2));
        agentLabs.push_back(lab);
    }
}

void ScoreMenu::setAgent(QString agentName)
{
    std::vector<int> scores = getScores(agentName);
    if(agentName == Game::LEARNING){
        setAgentLabels(scores,learning);
    }else if (agentName == Game::MINIMAX){
        setAgentLabels(scores,minimax);
    }else if (agentName == Game::EXPECTIMAX){
        setAgentLabels(scores,expectimax);
    }else{
        setAgentLabels(scores,keyboard);
    }
}

void ScoreMenu::setCombo(QStringList layouts)
{
    layoutsList=new QComboBox(this);
    layoutsList->addItems(layouts);
    layoutsList->setFont(QFont(ResourceLoader::FONT_NAME,cellSize/1.5));
    layoutsList->setMaximumWidth(cellSize*9);
    layoutsList->setMinimumWidth(cellSize*6);

}

void ScoreMenu::initLabels()
{
    for(int i =0;i<10;++i){
        learning.push_back(new QLabel(this));
        minimax.push_back(new QLabel(this));
        expectimax.push_back(new QLabel(this));
        keyboard.push_back(new QLabel(this));
    }
}
