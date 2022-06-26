#ifndef ROAD_H
#define ROAD_H
#include <QVector2D>
#include <QGraphicsItem>
#include <QPainter>
class Road: public QGraphicsLineItem
{
public:
    Road();
    ~Road();
//    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    QLineF getPathLine();
    float getRadius();
    virtual void advance(int phase);
private:
    QLineF path;
    QRectF rect;
    QPointF roadBegin;
    QPointF roadEnd;
    float radius;

};

#endif // ROAD_H
