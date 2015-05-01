#include "mainmenu.h"

const QString MainMenu::CONFIG_PATH = "config.cfg";
MainMenu::MainMenu()
{
    QFile f(CONFIG_PATH);
    QFontDatabase::addApplicationFont(":/fonts/Munro.ttf");
    GameOptions* opts = GameOptions::parseFromFile(f);
    cellSize = opts->cellSize;
    setContentsMargins(cellSize*5,cellSize*5,cellSize*5,cellSize*5);
    QFile style(":/stylesheets/stylesheets/button.qss"); //move to resouce loader
    style.open(QFile::ReadOnly);
    QString str = QLatin1String(style.readAll());
    setStyleSheet(str);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setSpacing(cellSize);
    setButtons(layout);
    connect(startButton,SIGNAL(clicked()),this,SLOT(startGame()));
    connect(exitButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(settings,SIGNAL(clicked()),this,SLOT(startSettings()));
    setLayout(layout);
    Util::center(*this);
    delete opts;
}

void MainMenu::startGame()
{

        QFile f(CONFIG_PATH);
        this->close();
        Canvas *v=new Canvas(*GameOptions::parseFromFile(f));
        v->show();
}

void MainMenu::startSettings()
{
    QFile f(CONFIG_PATH);
    Settings *s = new Settings(*GameOptions::parseFromFile(f));
    this->close();
    s->show();
}

void MainMenu::setButtons(QVBoxLayout* layout)
{
    layout->setAlignment(Qt::AlignHCenter);
    startButton = new QPushButton(this);
    startButton->setText("New Game");
    startButton->setFont(QFont("Munro",cellSize/1.5));
    startButton->setMinimumWidth(cellSize*10);
    startButton->setFocusPolicy(Qt::NoFocus);
    layout->addWidget(startButton);
    settings = new QPushButton(this);
    settings->setText("Options");
    settings->setFont(QFont("Munro",cellSize/1.5));
    settings->setFocusPolicy(Qt::NoFocus);
    layout->addWidget(settings);
    exitButton = new QPushButton(this);
    exitButton->setText("Exit");
    exitButton->setFont(QFont("Munro",cellSize/1.5));
    exitButton->setFocusPolicy(Qt::NoFocus);
    layout->addWidget(exitButton);
}


