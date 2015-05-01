#include "trainingwindow.h"



TrainingWindow::TrainingWindow(Game *g,Canvas* can):
    game(g),
    canvas(can),
    finished(false)
{
      setObjectName("trainWindow");
      QFile style(":/stylesheets/stylesheets/button.qss"); //move to resouce loader
      style.open(QFile::ReadOnly);
      QString str = QLatin1String(style.readAll());
      setStyleSheet(str);
      setWindowFlags(Qt::FramelessWindowHint);

      setGeometry(0,0,can->getCellSize()*10,can->getCellSize()*5);
      QVBoxLayout* layout = new QVBoxLayout(this);
      layout->setAlignment(Qt::AlignCenter);
      text = new QLabel;
      text->setText("Learning!");
      text->setFont(QFont("Munro",canvas->getCellSize()));
      layout->addWidget(text);
      bar = new QProgressBar(this);
      bar->setMinimum(0);
      bar->setMaximum(g->getTotalIters());
      layout->addWidget(bar);
      stop = new QPushButton();
      stop->setText("Stop Learning");
      stop->setFont(QFont("Munro",canvas->getCellSize()/1.5));
      stop->setFocusPolicy(Qt::NoFocus);
      layout->addWidget(stop);
      setLayout(layout);
      learnTimer = new QTimer();
      connect(learnTimer,SIGNAL(timeout()),this,SLOT(trainLoop()));
      connect(stop,SIGNAL(clicked()),this,SLOT(stopTrain()));
      learnTimer->start(1);
      Util::center(*this);
}

bool TrainingWindow::isFinished()
{
    return finished;
}

void TrainingWindow::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void TrainingWindow::trainLoop()
{
    if(game->isLearning()){
        int iter = game->trainStep();
        bar->setValue(iter);
    }else{
        learnTimer->stop();
        finished = true;
        canvas->show();
        canvas->startGame();

        this->close();
    }
}

void TrainingWindow::stopTrain()
{
    learnTimer->stop();
    game->restartGame();
    canvas->show();
    canvas->startGame();
    this->close();
}

