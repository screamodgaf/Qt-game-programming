#include <iostream>
#include "player.h"
Player::Player(std::vector<QPointF> vRoadPoints, QGraphicsScene *scene, QPointF location): m_scene{scene}, loc{location}, m_vRoadPoints{vRoadPoints}
{

    //    loc = { 0,200};
    vel = {2.f ,0.f }; ///seting innitial movement direction
    acc = {0.f ,0.f };

    //    radius = m_road->getRadius();
    radius = 30;
    ///triangle shape:
    //    triangle.append(QPointF(20, -30));
    //    triangle.append(QPointF(0,70));
    //    triangle.append(QPointF(-20, -30));
    //    this->setPolygon(triangle); /// for this QGraphicsPolygonItem
    //            this->setTransformOriginPoint(triangle.boundingRect().width()/2  ,
    //                                          triangle.boundingRect().height()/2
    //                                          );



    pixmap = new QPixmap;
    pixmap->load(":/car/car1.png");
    *pixmap = pixmap->scaled(100,102);
    QTransform t;
    t.rotate(180);
    *pixmap = pixmap->transformed(t);

    this->setPixmap(*pixmap);
//        this->setRotation(180);
//     this->setTransformOriginPoint(this->boundingRect().center());

};

void Player::applyForce(QVector2D& force)
{
    acc += force;
}

void Player::advance()
{
    vel += acc;
    loc += vel;
    this->setPos(loc.x(), loc.y() );
    acc = {0.f,0.f};
    predictFutureLoc(); ///sets futureLoc
    followPath();
    setRotationTowardTarget();
    qDebug() << vel;
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
    velCopy *=   125;
    futureLoc = loc + velCopy;
}


void Player::followPath()
{
    QVector2D pointAheadNormalPoint;
    int currentClosest = 100000 ;
    ///closestToShipPointOnPath = normal point is the point on the path, perpendicular to ship (thus closest to the ship) - so its finding point of the pathLine, that is closest to the future location:


    for (int i = 0; i < m_vRoadPoints.size(); ++i) {

        roadBegin =  m_vRoadPoints[i] ;
        roadEnd   =  m_vRoadPoints[i+1 % m_vRoadPoints.size()]; ///key idea is the wrap around points

        QPointF futureLocPoint = {futureLoc.x(), futureLoc.y() };
        ///estimate normal point:
        closestToFuturePointOnPath = calculateScalarProjectionVec( roadBegin, roadEnd, futureLocPoint);

        ///checking if closestToFuturePointOnPath is on the path (if its not extrapolating beyond path's length):
        ///creating temporary QLineF to use QLineF::contains(QPointF) method
        QLineF tempLine  = {roadBegin , roadEnd};
        QGraphicsLineItem item(tempLine);
        ///if closestToFuturePointOnPath is NOT on path, set the end of path as closestToFuturePointOnPath | without it vehicle goes straight for the last segment:
        if(!item.contains(closestToFuturePointOnPath.toPointF())){
            closestToFuturePointOnPath = { static_cast<float>(roadEnd.x()),
                                           static_cast<float>(roadEnd.y()) };


        }
        //        if(closestToFuturePointOnPath.x() < std::min(tempLine.p1().x(), tempLine.p2().x()) || ///Returns the smaller of the given values.
        //           closestToFuturePointOnPath.x() > std::max(tempLine.p1().x(), tempLine.p2().x()) ||
        //           closestToFuturePointOnPath.y() < std::min(tempLine.p1().y(), tempLine.p2().y()) ||
        //           closestToFuturePointOnPath.y() > std::max(tempLine.p1().y(), tempLine.p2().y()) ){
        //            closestToFuturePointOnPath = { static_cast<float>(roadEnd.x()),
        //                                           static_cast<float>(roadEnd.y()) };
        //        }


        distance = std::sqrt( ((closestToFuturePointOnPath.x() - futureLoc.x()) *
                               (closestToFuturePointOnPath.x() - futureLoc.x())) +
                              ((closestToFuturePointOnPath.y() - futureLoc.y()) *
                               (closestToFuturePointOnPath.y() - futureLoc.y())));


        if(distance < currentClosest)
        {
            currentClosest = distance;
            target = closestToFuturePointOnPath;

            ///setting point on the path, that is ahead of normal point - so it becomes the target for the ship:
            pointAheadNormalPoint = {static_cast<float>(roadEnd.x() - roadBegin.x()),
                                     static_cast<float>(roadEnd.y() - roadBegin.y()) }; ///roadEnd - roadBegin
            pointAheadNormalPoint.normalize();
            pointAheadNormalPoint *= 20 ;

            target = closestToFuturePointOnPath + pointAheadNormalPoint;

        }
    }
    seekTarget(target);
}

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
    //    QPen trianglePen(Qt::green, 3);
    //    trianglePen.setStyle(Qt::PenStyle::DashDotLine);
    //    painter->setPen(trianglePen);
    //    painter->drawPolygon(this->polygon());

    QPen locShip(Qt::red, 20);
    painter->setPen(locShip);
    painter->drawEllipse(mapFromScene(loc.x(), loc.y()), 1 ,1  );

    QPen futurePen(Qt::white, 20);
    painter->setPen(futurePen);
    painter->drawEllipse(mapFromScene(futureLoc.x()  , futureLoc.y()), 1,1);


    QPen closestToFuturePointOnPath_Pen(Qt::yellow, 20);
    painter->setPen(closestToFuturePointOnPath_Pen);
    painter->drawEllipse(mapFromScene(closestToFuturePointOnPath.x(),
                                      closestToFuturePointOnPath.y()), 1,1);


    // painter->drawPixmap(pixmap->rect(), *pixmap);

    // painter->draw(this);

    painter->drawPixmap(-pixmap->width()/2 ,0, *pixmap);


}

void Player::seekTarget(QVector2D target)
{
    float maxSpeed = 1.8f;
    float maxForce = 0.018f;


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
    return pixmap->rect();
}


void Player::setRotationTowardTarget()
{
    ///player rotation toward target:
    //        QVector2D distBetweenPoints(((target->x() + target->boundingRect().width()/2)
    //                                     - (this->x() + this->boundingRect().width()/2)),

    //                                    (target->y() + target->boundingRect().height()/2)
    //                                    - (this->y() + this->boundingRect().height()/2));

    double rad = std::atan2(vel.y(), vel.x()); //    float rotation = std::atan2(player->y() - target->pos().y(),  player->x() - target->pos().x()) *270.f/M_PI;
    double degrees =  rad* 180.f /M_PI;
    degrees = normalize_angle(degrees);
    this->setRotation(degrees+270.f);
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
    delete pixmap;
    pixmap = nullptr;
    qDebug() << "~Player()";
}
