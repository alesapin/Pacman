#include "scoretext.h"

const QString ScoreText::SCORE = "Score: ";

ScoreText::ScoreText(QPointF position, int cellSize)
{
    scoreNum = 0;
    setBrush(QBrush(Qt::white));
    setFont(QFont("Munro",cellSize));
    setPos(position);
}

void ScoreText::updateScore(int num)
{
    scoreNum = num;
    setText(SCORE + QString::number(num));
}
