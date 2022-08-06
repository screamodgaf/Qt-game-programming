#include "item.h"
#include <QRandomGenerator>
#include <iostream>
Item::Item()
{

    rect.setSize(QSize(80.f,80.f));

}

QRectF Item::boundingRect() const ///The boundingRect() function defines the outer bounds of the item as a rectangle. Note that the Graphics View framework uses the bounding rectangle to determine whether the item requires redrawing, so all painting must be done inside this rectangle.
{
    return rect;
}

QPainterPath Item::shape() const   ///the actual collision detection is handled by the Graphics View framework using shape-shape intersection. All we have to do is to ensure that the QGraphicsItem::shape() function returns an accurate shape for our item:
{
    QPainterPath path;
    path.addRect(rect);
    return path;
}

void Item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) //The Graphics View framework calls the paint() function to paint the contents of the item; the function paints the item in local coordinates.
{
    painter->setBrush(m_color);
    painter->drawRect(0, 0, 80, 80);
}

void Item::advance(int step)
{
    if (!step) return;

 ;
}

void Item::setColour(QColor& c)
{
    m_color = c;
}

Item::~Item()
{

}
