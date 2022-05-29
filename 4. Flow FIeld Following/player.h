#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsItem>
#include <QPainter>
#include <QVector2D>
class FlowField;
class Player: public QGraphicsPolygonItem
{
public:
    Player(FlowField* flowField);
    virtual ~Player();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
    void applyForce(QVector2D& force);
    void advance();
    QVector2D getVelocity();
    void calculateSteeringForce();
    void setRotationTowardTarget();
    float normalize_angle(const float value );
private:
    QRectF rect;
    QVector2D loc;
    QVector2D vel;
    QVector2D acc;

    QPolygonF triangle;

    FlowField* m_flowField = nullptr;
};

#endif // PLAYER_H
