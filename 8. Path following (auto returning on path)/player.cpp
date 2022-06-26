#include <iostream>
#include "player.h"
Player::Player(Road *road, QGraphicsScene *scene, QPointF location): m_scene{scene}, m_road{road}, loc{location}
{
    rect.setRect(0,0,5,30);
//    loc = { 0,200};
    vel = {2.3f ,2.3f };
    acc = {0.f ,0.f };

    radius = m_road->getRadius();
    ///triangle shape:
    triangle.append(QPointF(20, -30));
    triangle.append(QPointF(0,70));
    triangle.append(QPointF(-20, -30));
    this->setPolygon(triangle); /// for this QGraphicsPolygonItem
//    this->setTransformOriginPoint(triangle.boundingRect().width()/2  ,
//                                  triangle.boundingRect().height()/2
//                                  );

    roadBegin = { m_road->getPathLine().p1().x(),
                  m_road->getPathLine().p1().y() };
    roadEnd   = { m_road->getPathLine().p2().x(),
                  m_road->getPathLine().p2().y() };

}

void Player::applyForce(QVector2D& force)
{
    acc += force;
}

void Player::advance()
{
    vel += acc;
    loc += vel;
    this->setPos(loc.x(), loc.y());
    acc = {0.f,0.f};
    predictFutureLoc(); ///sets futureLoc
    followPath();
    setRotationTowardTarget();

//    qDebug() << "loc: " << loc << " scene: " << this->scenePos();
}




QVector2D Player::getVelocity()
{
    return vel;
}

void Player::predictFutureLoc()
{
    QVector2D velCopy = getVelocity();
    velCopy.normalize();
    velCopy *= 125;
    futureLoc = loc + velCopy;
}


void Player::followPath()
{

    ///closestToShipPointOnPath = normal point is the point on the path, perpendicular to ship (thus closest to the ship) - so its finding point of the pathLine, that is closest to the future location:

    QPointF futureLocPoint = {futureLoc.x(), futureLoc.y()};

//    qDebug() << "roadBegin: " << roadBegin;
//    qDebug() << "roadEnd: " << roadEnd;
//    qDebug() << "futureLocPoint: " << futureLocPoint;
//    qDebug() << "loc: " << loc;
//    qDebug() << "closestToFuturePointOnPath: " << closestToFuturePointOnPath;
//    qDebug() << "--------------" ;
    closestToFuturePointOnPath = calculateScalarProjectionVec( roadBegin, roadEnd, futureLocPoint);
    ///setting point on the path, that is ahead of normal point - so it becomes the target for the ship:
    QVector2D pointAheadNormalPoint = {static_cast<float>(roadEnd.x() - roadBegin.x()),
                        static_cast<float>(roadEnd.y() - roadBegin.y()) }; ///roadEnd - roadBegin
    pointAheadNormalPoint.normalize();
    pointAheadNormalPoint *= 10;
    target = closestToFuturePointOnPath + pointAheadNormalPoint;

    ///check distance between normal point and predicted location:
    /// sqrt(dx*dx+dy*dy)
    float distance =
    std::sqrt( ((closestToFuturePointOnPath.x() - futureLoc.x()) * (closestToFuturePointOnPath.x() - futureLoc.x()) ) +
               ((closestToFuturePointOnPath.y() - futureLoc.y()) * (closestToFuturePointOnPath.y() - futureLoc.y()) ) );
//    qDebug() << "distance: " << distance;
    if(  distance  > radius  ) seekTarget(target);
}

//void Player::calculateScalarProjection(const QVector2D& v1, const QVector2D& v2)
QVector2D Player::calculateScalarProjectionVec(QPointF& roadBegin, QPointF& roadEnd,
                                               QPointF& futureLocPoint)
{
    ///scalar projection is the length of the vector projection
    ///QPointF roadBegin is the prigin point

    ///vectorProjected is a vector that starts from roadBegin and ends at ships' future location
//    QVector2D vectorProjected;
    vectorProjected.setX(futureLocPoint.x() - roadBegin.x());
    vectorProjected.setY(futureLocPoint.y() - roadBegin.y());

    QVector2D pathVector;
    pathVector.setX( roadEnd.x() - roadBegin.x()  );
    pathVector.setY( roadEnd.y() - roadBegin.y() );

    scalarProjectionVec = pathVector.normalized();
    /// dotProduct gives the length of the shadow (scalarProjection vector) cast
    float dotProduct = QVector2D::dotProduct(vectorProjected, scalarProjectionVec);

    scalarProjectionVec *= dotProduct;
//scalarProjectionVec = {scalarProjectionVec.x(), 400};

    scalarProjectionVec = { static_cast<float>(scalarProjectionVec.x() + roadBegin.x()),
                            static_cast<float>(scalarProjectionVec.y() + roadBegin.y()) };
    return scalarProjectionVec;
}






void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    ///when drawing - it should be in scene coordinates, not player's coordinates
    QPen trianglePen(Qt::green, 3);
    trianglePen.setStyle(Qt::PenStyle::DashDotLine);
    painter->setPen(trianglePen);
    painter->drawPolygon(this->polygon());

    QPen locShip(Qt::red, 20);
    painter->setPen(locShip);
    painter->drawEllipse(mapFromScene(loc.x(), loc.y()), 1 ,1  );

    QPen futurePen(Qt::green, 20);
    painter->setPen(futurePen);
    painter->drawEllipse(mapFromScene(futureLoc.x()  , futureLoc.y()), 1,1);

    QPen linePen(Qt::white, 1);
    painter->setPen(linePen);
    painter->drawLine(mapFromScene(loc.x(), loc.y()),
                      mapFromScene(futureLoc.x()  , futureLoc.y()));

    QPen closestToFuturePointOnPath_Pen(Qt::yellow, 20);
    painter->setPen(closestToFuturePointOnPath_Pen);
    painter->drawEllipse(mapFromScene(closestToFuturePointOnPath.x(),
                                      closestToFuturePointOnPath.y()), 1,1);

    QPen line1(Qt::yellow, 1);
    painter->setPen(line1);
    painter->drawLine(mapFromScene(roadBegin.x(), roadBegin.y()),
                      mapFromScene(futureLoc.x()  , futureLoc.y()));

    QPen line2(Qt::red, 2);
    painter->setPen(line2);
    painter->drawLine(mapFromScene(roadBegin.x(), roadBegin.y()),
                      mapFromScene(roadEnd.x()  , roadEnd.y()));



}

void Player::seekTarget(QVector2D target)
{
    float maxSpeed = 2;
    float maxForce = 0.01;

    QVector2D desiredVel = QVector2D(target - loc);
    ///setting magnitude to max speed (normalizing to length 1 and sacaling by multiplying by maxSpeed):
    desiredVel.normalize();
    desiredVel *= maxSpeed;

    ///Reynolds formula:
    QVector2D steering = desiredVel - this->getVelocity();
    ///limit force by setting max force to maxForce:
    steering.normalize();
    steering*= maxForce;
//qDebug()<< "steering: " << steering;
    this->applyForce(steering);
}



QRectF Player::boundingRect() const
{
    return rect;
}


void Player::setRotationTowardTarget()
{
    ///player rotation toward target:
    //        QVector2D distBetweenPoints(((target->x() + target->boundingRect().width()/2)
    //                                     - (this->x() + this->boundingRect().width()/2)),

    //                                    (target->y() + target->boundingRect().height()/2)
    //                                    - (this->y() + this->boundingRect().height()/2));

    double rad = std::atan2(vel.y(), vel.x()); //    float rotation = std::atan2(player->y() - target->pos().y(),  player->x() - target->pos().x()) *270.f/M_PI;
    double degrees =  rad* 180.0 /M_PI;
    degrees = normalize_angle(degrees);
    this->setRotation(degrees+270);
}

float Player::normalize_angle(const float value) {
    float start = -180.f;
    float end = 180.f;
    float width = end - start   ;
    float offsetValue = value - start ;
    return ( offsetValue - ( floor( offsetValue / width ) * width ) ) + start ;
}

Player::~Player()
{
    qDebug() << "~Player()";
}
