#ifndef ITEM_H
#define ITEM_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
class Item : public QGraphicsItem
{
public:
    Item();
    QRectF boundingRect() const override; //pure virtual public function - When writing a custom graphics item, you must implement QGraphicsItem's two pure virtual public functions: boundingRect(), which returns an estimate of the area painted by the item, and paint(), which implements the actual painting. In addition, we reimplement the shape() and advance().
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, //pure virtual public function
               QWidget *widget) override;

protected:
    virtual void advance(int step) override;
private:
    qreal angle = 0;
    qreal speed = 0;
    qreal direction = 0;
    QColor color;

    QRectF rect;
};

#endif // ITEM_H
