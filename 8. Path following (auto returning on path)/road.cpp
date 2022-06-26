#include "road.h"
#include <iostream>
Road::Road()
{


    roadBegin = {0,400};
    roadEnd = {11600, 400};
    path.setP1(roadBegin);
    path.setP2(roadEnd);
    radius = 30;

    this->setLine(path);
//rect = boundingRect();

//rect = QRectF(roadBegin.x(),
//              roadBegin.y(),
//              roadEnd.x() - roadBegin.x(),
//              roadEnd.y() - roadBegin.y());

}


//QRectF Road::boundingRect() const
//{

//    return  rect;
//}

void Road::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QBrush b(Qt::white);
    QPen p(b, 10);
    p.setStyle(Qt::PenStyle::DashLine);
    painter->setPen(p);
    painter->drawLine(this->line());


    ///================== upper road bountry:
    QPen lineUpperPen(Qt::white, 3);
    painter->setPen(lineUpperPen);
    QLineF upperLineBoundry = { QPointF(path.x1(), path.y1()-radius),
                                QPointF(path.x2(), path.y2()-radius)};
    painter->drawLine(upperLineBoundry);

    QLineF bottomLineBoundry = { QPointF(path.x1(), path.y1()+radius),
                                QPointF(path.x2(), path.y2()+radius)};
    painter->drawLine(bottomLineBoundry);

}

QLineF Road::getPathLine()
{
    return path;
}

float Road::getRadius()
{
    return radius;
}

void Road::advance(int phase)
{

}


Road::~Road()
{
    qDebug() << " Road::~Road() ";
}
