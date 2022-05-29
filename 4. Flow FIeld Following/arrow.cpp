#include "arrow.h"

Arrow::Arrow()
{
//    qDebug() << "Arrow() ctor - pos: " << pos() << " rotation: " << rotation();
    rect.setRect(0,0,100,100);
//    line.setPoints(QPoint(0,50), QPoint(100, 50));
    polygon << QPoint(0,45)  << QPoint(60,45) << QPoint(60,35) << QPoint(100, 50) <<
               QPoint(60,65) << QPoint(60,55) << QPoint(0,55)  << QPoint(0,45);
    setTransformOriginPoint(boundingRect().center());
}

QRectF Arrow::boundingRect() const
{
     return rect;
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//        QPen linePen(Qt::yellow, 3);
//        painter->setPen(linePen);
//        painter->setRenderHint(QPainter::Antialiasing);
            QBrush pen(Qt::yellow);
            painter->setBrush(pen);
            painter->setRenderHint(QPainter::Antialiasing);
            painter->drawPolygon(polygon);
}

void Arrow::advance()
{

}

QVector2D Arrow::getRotationVector()
{
    /// Vector2( cos(radians),  sin(radians))

//    qDebug() << "currentRotatinDegrees: " << rotation() << "address: " << this;
    float radRotation = rotation() * (M_PI / 180); ///degree to radian
//    qDebug() << "radRotation: " << radRotation;
    QVector2D direction = { static_cast<float>(std::cos(radRotation)),
                            static_cast<float>(std::sin(radRotation)) };
    return direction;
}
