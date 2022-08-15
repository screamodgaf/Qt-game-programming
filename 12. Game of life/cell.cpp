#include "cell.h"
#include <QRandomGenerator>
#include <iostream>
Cell::Cell(int size): m_size{size}
{
    m_rect.setSize(QSize(m_size, m_size));
}

QRectF Cell::boundingRect() const ///The boundingRect() function defines the outer bounds of the item as a rectangle. Note that the Graphics View framework uses the bounding rectangle to determine whether the item requires redrawing, so all painting must be done inside this rectangle.
{
    return m_rect;
}

QPainterPath Cell::shape() const   ///the actual collision detection is handled by the Graphics View framework using shape-shape intersection. All we have to do is to ensure that the QGraphicsItem::shape() function returns an accurate shape for our item:
{
    QPainterPath path;
    path.addRect(m_rect);
    return path;
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) //The Graphics View framework calls the paint() function to paint the contents of the item; the function paints the item in local coordinates.
{
    if(m_color == Qt::black)
        return;
    painter->setBrush(m_color);
    painter->drawRect(0, 0, m_size, m_size);
}

void Cell::advance(int step)
{
    if (!step) return;


}

void Cell::setColor(QColor c)
{
    m_color = c;
}

QColor Cell::getColor()
{
    return m_color;
}

Cell::~Cell()
{

}
