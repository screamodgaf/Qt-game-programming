#ifndef CELL_H
#define CELL_H
#include <QGraphicsItem>
#include <QPainter>
class Cell: public QGraphicsItem
{
public:
    Cell(int size);
    ~Cell();
    QRectF boundingRect() const override; //pure virtual public function - When writing a custom graphics item, you must implement QGraphicsItem's two pure virtual public functions: boundingRect(), which returns an estimate of the area painted by the item, and paint(), which implements the actual painting. In addition, we reimplement the shape() and advance().
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, //pure virtual public function
               QWidget *widget) override;

    QColor getColor();
    void setColor(QColor c);

protected:
    virtual void advance(int step) override;

protected:
private:
    qreal angle = 0;
    qreal speed = 0;
    qreal direction = 0;
    QColor m_color;

    QRectF m_rect;
    int m_size;
};

#endif // CELL_H
