#include "road.h"
#include <iostream>
Road::Road(QPointF roadBegin, QPointF roadEnd)
{
    path.setP1(roadBegin);
    path.setP2(roadEnd);
    radius = 30;

    this->setLine(path);


}


void Road::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QBrush b(Qt::black);
    QPen p(b, 100);
    p.setCapStyle(Qt::RoundCap);
    p.setStyle(Qt::PenStyle::SolidLine);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(p);
    painter->drawLine(this->line());



}

QPointF Road::rotatePointAroundBase(QPointF point, QPointF base, float angle)
{
    float sin_ = std::sin(angle*M_PI/180);
    float cos_ = std::cos(angle*M_PI/180);
    point -= base;
    QPointF point_rotated;
    point_rotated.setX (point.x() * cos_ - point.y() * sin_);
    point_rotated.setY( point.x() * sin_ + point.y() * cos_);
    point_rotated+=base;
    return point_rotated;
}


QLineF Road::getPathLine()
{
    return path;
}

float Road::getRadius()
{
    return radius;
}




Road::~Road()
{
    qDebug() << " Road::~Road() ";
}
