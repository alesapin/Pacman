#ifndef ACTIONS_H
#define ACTIONS_H
#include <map>
#include "agents/agent.h"
#include <QPointF>
#include "configuration.h"
/**
 * @brief The Actions class
 * Класс состоящий из статических методов
 * Предназначен для превращения направлений в конкретные точки
 * , а так же получения возможных действий при конкретной конфигурации
 */
class Actions
{
public:
    /**
     * @brief reverseDirection метод возвращает направление
     * обратное переданному
     * @param direction - направлие
     * @return обратное направление
     */
    static Direction reverseDirection(Direction direction);
    /**
     * @brief vectorToDirection Согласно map - directions, превращает заданный вектор(x,y) в
     * конкретное направление
     * @param vect вектор из 2-ух чисел
     * @return направление, соответствующее вектору
     */
    static Direction vectorToDirection(QPointF vect);
    /**
     * @brief directionToVector Возвращает конкретный вектор(x,y)
     * полученный в результате движения в заданном направление
     * с заданной скоростью
     * @param dir направление
     * @param speed скорость
     * @return  вектор
     */
    static QPointF directionToVector(Direction dir=STOP,double speed = 1.0);
    /**
     * @brief getPossibleActions Возвращает возможные направления
     * для заданной конфигурации и матрицы стен
     * @param config конфигурация
     * @param walls стены
     * @return список направлений
     */
    static std::vector<Direction> getPossibleActions(Configuration& config,const std::vector <std::vector <bool> >& walls);
    static std::vector<QPointF> getLegalNeighbours(QPointF position,std::vector <std::vector <bool> > walls);
    /**
     * @brief getSuccessor возвращает вектор полученый в резултатте
     * движения из точки в заданном направлении
     * @param point - точка
     * @param dir - направление
     * @return  вектор
     */
    static QPointF getSuccessor(QPointF point,Direction dir);
private:
    /**
    * @brief directions Карта направлений и соответствующих векторов
    */
   static std::map<Direction,QPointF>  directions;
   /**
    * @brief TOLERANCE Точность движения пакмана в ячейке, чтобы
    * нельзя было ходить по частям ячеек
    */
   static const double TOLERANCE;
};

#endif // ACTIONS_H
