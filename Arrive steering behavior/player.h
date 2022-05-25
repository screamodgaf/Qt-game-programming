#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsItem>
#include <QPainter>
#include <QVector2D>
class Player: public QGraphicsPolygonItem
{
public:
    Player();
    virtual ~Player();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
    void applyForce(QVector2D& force);
    void advance();
    QVector2D getVelocity();
private:
    QRectF rect;
    QVector2D loc;
    QVector2D vel;
    QVector2D acc;

    QPolygonF triangle;
};

#endif // PLAYER_H
