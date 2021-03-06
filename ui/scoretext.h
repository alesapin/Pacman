#ifndef SCORETEXT_H
#define SCORETEXT_H
#include <QGraphicsSimpleTextItem>
#include <QString>
#include <QFont>
#include <QBrush>
class ScoreText : public QGraphicsSimpleTextItem
{
public:
    ScoreText(QPointF pos,int cellSize,int width);
    void updateScore(int num);
    int getScore();
    static const QString SCORE;
    int scoreNum;
};

#endif // SCORETEXT_H
