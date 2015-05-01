#include "gameovermenu.h"



GameOverMenu::GameOverMenu(Canvas *cnv):
    canvas(cnv)
{
    setWindowFlags(Qt::FramelessWindowHint);
    this->setObjectName("gameOverWindow");
    QFile style(":/stylesheets/stylesheets/button.qss"); //move to resouce loader
    style.open(QFile::ReadOnly);
    QString str = QLatin1String(style.readAll());
    setStyleSheet(str);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QHBoxLayout* label1 = new QHBoxLayout();
    QHBoxLayout* label2 = new QHBoxLayout();

    buttonLayout->setAlignment(Qt::AlignCenter);
    label1->setAlignment(Qt::AlignCenter);
    label2->setAlignment(Qt::AlignCenter);
    mainLayout->setAlignment(Qt::AlignCenter);
    gameOver = new QLabel();
    gameOver->setText("Game Over!");
    gameOver->setFont(QFont("Munro",canvas->getCellSize()/1.5));
    label1->addWidget(gameOver);
    score = new QLabel();
    score->setText(canvas->getScore());
    score->setFont(QFont("Munro",canvas->getCellSize()/1));
    label2->addWidget(score);




    setGeometry(0,0,cnv->getCellSize()*10,cnv->getCellSize()*10);
    mainLayout->setSpacing(cnv->getCellSize());
    restart = new QPushButton(this);
    restart->setText("Restart");
    restart->setFont(QFont("Munro",canvas->getCellSize()/1.5));
    restart->setFocusPolicy(Qt::NoFocus);
    restart->setMinimumWidth(canvas->getCellSize()*5);
    restart->setMaximumWidth(canvas->getCellSize()*7);
    buttonLayout->addWidget(restart);
    toMenu = new QPushButton(this);
    toMenu->setText("Exit to Menu");
    toMenu->setFont(QFont("Munro",canvas->getCellSize()/1.5));
    toMenu->setMinimumWidth(canvas->getCellSize()*5);
    toMenu->setMaximumWidth(canvas->getCellSize()*7);
    toMenu->setFocusPolicy(Qt::NoFocus);
    buttonLayout->addWidget(toMenu);
    mainLayout->addLayout(label1);
    mainLayout->addLayout(label2);
    mainLayout->addLayout(buttonLayout);
    connect(restart,SIGNAL(clicked()),this,SLOT(restartGame()));
    connect(toMenu,SIGNAL(clicked()),this,SLOT(exitToMenu()));
    Util::center(*this);
}

void GameOverMenu::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void GameOverMenu::restartGame()
{
    canvas->setEnabled(true);
    this->close();
    canvas->restartGame();
}

void GameOverMenu::exitToMenu()
{
    canvas->setEnabled(true);
    canvas->close();
    MainMenu *m = new MainMenu();
    this->close();
    m->show();
}
