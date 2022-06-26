#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsItem>
#include <QPainter>
#include <QVector2D>
#include "road.h"
#include <QGraphicsScene>
class Player: public QGraphicsPolygonItem
{
public:
    Player(Road* road, QGraphicsScene* scene, QPointF location);
    virtual ~Player();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
    void applyForce(QVector2D& force);
    void advance();
    QVector2D getVelocity();
    void followPath();
    void predictFutureLoc();
    QVector2D calculateScalarProjectionVec(QPointF &roadBegin, QPointF &roadEnd, QPointF &futureLocPoint);
    void seekTarget(QVector2D target);
private:
    void setRotationTowardTarget();
    float normalize_angle(const float value);
private:
    QGraphicsScene* m_scene = nullptr;;

    Road* m_road = nullptr;
    QRectF rect;
    QVector2D loc;
    QVector2D vel;
    QVector2D acc;
    QPolygonF triangle;
    float radius;
    QVector2D target;
    QPointF roadBegin;
    QPointF roadEnd;
    QVector2D closestToFuturePointOnPath;
    QVector2D futureLoc;
    QVector2D scalarProjectionVec;
    QVector2D vectorProjected;

};

#endif // PLAYER_H
