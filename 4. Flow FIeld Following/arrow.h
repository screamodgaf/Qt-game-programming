#ifndef ARROW_H
#define ARROW_H
#include <QGraphicsPolygonItem>
#include <QPainter>
#include <QPen>
#include <QVector2D>
#include <QDebug>
class Arrow: public QGraphicsPolygonItem
{
public:
    Arrow();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
    void applyForce(QVector2D& force);
    void advance();
    QVector2D getRotationVector();
private:
    QRectF rect;
//    QLine line;
    QPolygonF polygon;

};

#endif // ARROW_H
