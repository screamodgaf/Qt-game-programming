#include "player.h"
#include <iostream>
#include "flowfield.h"
Player::Player(FlowField* flowField): m_flowField {flowField}
{
    rect.setRect(0,0,5,30);
    loc = {1400.f ,1300.f };
    vel = {0.f ,0.f };
    acc = {0.f ,0.f };

    ///triangle shape:
    triangle.append(QPointF(40.f,0.f));
    triangle.append(QPointF(20.f,100.f));
    triangle.append(QPointF(0.f,0.f));
    this->setPolygon(triangle); /// for this QGraphicsPolygonItem
    this->setTransformOriginPoint(triangle.boundingRect().center().x()
                                  , triangle.boundingRect().center().y() -10); ///-10 prevents rapid turns and shaking
}

void Player::applyForce(QVector2D& force)
{
    acc += force;
}
void Player::calculateSteeringForce()
{
    float maxSpeed = 3.f;
    float maxForce = 0.10; ///how sharp the turns are
    Arrow* a = m_flowField->getField(this->x(), this->y()); //null??
    if(a == nullptr) return;
//    qDebug() << "a address at " << this->x() << " " << this->y() << " : " << a;
    QVector2D desiredVel = a->getRotationVector();
    ///setting magnitude to maxSpeed (normalizing to length 1 and scaled by multiplying by maxSpeed)
//    desiredVel.normalize(); ///already is normalized as its unit vector
    desiredVel *= maxSpeed;

    ///Reynolds formula:
    QVector2D steering = desiredVel - getVelocity();
    ///limit force by setting maximum force to maxForce:
    steering.normalize();
    steering *= maxForce;
    qDebug() << steering;
    applyForce(steering);
}

float Player::normalize_angle(const float value ) {
    float start = -180.f;
    float end = 180.f;
    float width = end - start   ;
    float offsetValue = value - start ;
    return ( offsetValue - ( floor( offsetValue / width ) * width ) ) + start ;
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

void Player::advance()
{
    calculateSteeringForce();

    vel += acc;
    loc += vel;
    this->setPos(loc.x(), loc.y());

    acc = {0.f,0.f};
    setRotationTowardTarget();
}

QVector2D Player::getVelocity()
{
    return vel;
}

QRectF Player::boundingRect() const
{
    return rect;
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush(Qt::red);
    painter->setBrush(brush);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawPolygon(triangle);



    QPen pen(Qt::green,10);
    painter->setPen(pen);
    painter->drawPoint(this->transformOriginPoint());
}

Player::~Player()
{
    qDebug() << "~Player()";
}
