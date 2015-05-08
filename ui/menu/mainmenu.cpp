#include "mainmenu.h"

const QString MainMenu::CONFIG_PATH = "config.cfg";
MainMenu::MainMenu()
{
    setWindowTitle("Pacman");
    GameOptions* opts = GameOptions::parseFromFile();
    cellSize = opts->cellSize;
    setContentsMargins(cellSize*5,cellSize*5,cellSize*5,cellSize*5);

    setStyleSheet(ResourceLoader::STYLE);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setSpacing(cellSize);
    setButtons(layout);
    connect(startButton,SIGNAL(clicked()),this,SLOT(startGame()));
    connect(exitButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(settings,SIGNAL(clicked()),this,SLOT(startSettings()));
    connect(scores,SIGNAL(clicked()),this,SLOT(startScore()));
    setLayout(layout);
    Util::center(*this);
    delete opts;
}

void MainMenu::startGame()
{

        this->close();
        Canvas *v=new Canvas(*GameOptions::parseFromFile());
        v->show();
}

void MainMenu::startSettings()
{
    Settings *s = new Settings(*GameOptions::parseFromFile());
    this->close();
    s->show();
}

void MainMenu::startScore()
{
    ScoreMenu *m = new ScoreMenu(cellSize);
    this->close();
    m->show();
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
    scores = new QPushButton(this);
    scores->setText("Score Table");
    scores->setFont(QFont("Munro",cellSize/1.5));
    scores->setFocusPolicy(Qt::NoFocus);
    layout->addWidget(scores);
    exitButton = new QPushButton(this);
    exitButton->setText("Exit");
    exitButton->setFont(QFont("Munro",cellSize/1.5));
    exitButton->setFocusPolicy(Qt::NoFocus);
    layout->addWidget(exitButton);

}


