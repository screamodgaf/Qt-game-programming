#ifndef ROAD_H
#define ROAD_H
#include <QVector2D>
#include <QGraphicsItem>
#include <QPainter>
class Road: public QGraphicsLineItem
{
public:
    Road(QPointF roadBegin, QPointF roadEnd);
    ~Road();
//    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    QLineF getPathLine();
    float getRadius();
    QPointF rotatePointAroundBase(QPointF point, QPointF base, float angle);
private:
    QLineF path;
    QRectF rect;
//    QPointF m_roadBegin;
//    QPointF m_roadEnd;
    float radius;

};

#endif // ROAD_H
