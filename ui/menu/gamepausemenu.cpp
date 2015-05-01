#include "gamepausemenu.h"
GamePauseMenu::GamePauseMenu(Canvas *cnv):
    canvas(cnv)
{
    setWindowFlags(Qt::FramelessWindowHint);
    this->setObjectName("gamePauseWindow");
    QFile style(":/stylesheets/stylesheets/button.qss"); //move to resouce loader
    style.open(QFile::ReadOnly);
    QString str = QLatin1String(style.readAll());
    setStyleSheet(str);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    setGeometry(0,0,cnv->getCellSize()*10,cnv->getCellSize()*10);
    layout->setSpacing(cnv->getCellSize());
    resume = new QPushButton(this);
    resume->setText("Resume");
    resume->setFont(QFont("Munro",canvas->getCellSize()/1.5));
    resume->setFocusPolicy(Qt::NoFocus);
    resume->setMinimumWidth(canvas->getCellSize()*5);
    resume->setMaximumWidth(canvas->getCellSize()*7);
    layout->addWidget(resume);
    toMenu = new QPushButton(this);
    toMenu->setText("Exit to Menu");
    toMenu->setFont(QFont("Munro",canvas->getCellSize()/1.5));
    toMenu->setMinimumWidth(canvas->getCellSize()*5);
    toMenu->setMaximumWidth(canvas->getCellSize()*7);
    toMenu->setFocusPolicy(Qt::NoFocus);
    layout->addWidget(toMenu);
    connect(resume,SIGNAL(clicked()),this,SLOT(resumeGame()));
    connect(toMenu,SIGNAL(clicked()),this,SLOT(returnToMenu()));
    Util::center(*this);
}

void GamePauseMenu::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void GamePauseMenu::resumeGame()
{
    this->close();
    canvas->setEnabled(true);
    canvas->unpause();
}

void GamePauseMenu::returnToMenu()
{
    canvas->setEnabled(true);
    canvas->close();
    MainMenu *m = new MainMenu();
    this->close();
    m->show();

}
