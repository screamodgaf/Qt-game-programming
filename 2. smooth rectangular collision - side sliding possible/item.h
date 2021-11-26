#ifndef ITEM_H
#define ITEM_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsBlurEffect>
class Item : public QGraphicsItem
{
public:
    Item();
    ~Item();
    QRectF boundingRect() const override; //pure virtual public function - When writing a custom graphics item, you must implement QGraphicsItem's two pure virtual public functions: boundingRect(), which returns an estimate of the area painted by the item, and paint(), which implements the actual painting. In addition, we reimplement the shape() and advance().
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, //pure virtual public function
               QWidget *widget) override;

    QGraphicsBlurEffect* getBlurEffect();
    void setColour(QColor& c);

protected:
    virtual void advance(int step) override;

protected:
private:
    qreal angle = 0;
    qreal speed = 0;
    qreal direction = 0;
    QColor m_color;

    QRectF rect;

     QGraphicsBlurEffect* m_blurEffect = nullptr;
};

#endif // ITEM_H
