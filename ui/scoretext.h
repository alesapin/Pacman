#ifndef SCORETEXT_H
#define SCORETEXT_H
#include <QGraphicsSimpleTextItem>
#include <QString>
#include <QFont>
#include <QBrush>
class ScoreText : public QGraphicsSimpleTextItem
{
public:
    ScoreText(QPointF pos,int cellSize);
    void updateScore(int num);
    static const QString SCORE;
    int scoreNum;
};

#endif // SCORETEXT_H
