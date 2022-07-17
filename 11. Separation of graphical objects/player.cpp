#include "player.h"
#include <iostream>
Player::Player(std::vector<Player*>* v_agents, QPointF p): m_v_agents{v_agents}
{
    this->rect.setRect(0,0,50,50);

    //    qDebug() << "this POS: " << this->pos();
    setPos({p.x(), p.y()});
    loc = {static_cast<float>(this->pos().x()),
           static_cast<float>(this->pos().y())};
    vel = {0.f ,0.f };
    acc = {0.f ,0.f };
    //qDebug() << "this POS: " << this->pos();
    ///triangle shape:
//    triangle.append(QPointF(40.f,0.f));
//    triangle.append(QPointF(20.f,100.f));
//    triangle.append(QPointF(0.f,0.f));
//    this->setPolygon(triangle); /// for this QGraphicsPolygonItem
    this->setTransformOriginPoint(triangle.boundingRect().center());

    colour.setRed(std::rand()%225);
    colour.setBlue(std::rand()%225);
    colour.setGreen(std::rand()%225);
}

void Player::applyForce(QVector2D& force)
{
    //        qDebug() << "force: " << force;
    acc += force;
}

void Player::advance()
{
    vel += acc;
    loc += vel;
    //    performSeparation();
    this->setPos(loc.x(), loc.y());

    acc = {0.f,0.f};
    //    vel = {0.f,0.f};

}

float maxSpeed = 2;
float maxForce = 1.11;
void Player::performSeparation()
{
    float separationDistance = 50;
    int count = 0;
    QVector2D sumOfVels = {0,0};

    for (int i = 0; i < m_v_agents->size(); ++i) {
                ///if(m_v_agents->at(i) == this) return; - not needed
        QVector2D neighbourLoc = m_v_agents->at(i)->getLocation();

        float dx = neighbourLoc.x() - loc.x();
        float dy = neighbourLoc.y() - loc.y();
        float distance = std::sqrt(dx*dx+dy*dy);

        if(distance > 0 && distance < separationDistance){
            QVector2D difference =  m_v_agents->at(i)->getLocation() - loc  ; /// if m_v_agents->at(i)->getLocation() - loc thats clumping, unless sumOfVels += -difference;
            difference.normalize();
            difference /=distance;
            sumOfVels += -difference;
            count++;

        }else vel*=0.01; ///dumping movement untill it stops
    }


    if(count >0){
        sumOfVels/=count;
        sumOfVels.normalize();
        sumOfVels*=maxSpeed;
        QVector2D steerForce = sumOfVels - vel;
        steerForce.normalize();
        steerForce*=maxForce;
        applyForce(steerForce);
    }

}

QVector2D Player::getVelocity()
{
    return vel;
}

QVector2D Player::getLocation()
{
    return loc;
}

void Player::setLocation(QVector2D loc_)
{
    loc = loc_;
}

//void Player::restrictToEdges()
//{
//    if(y()<0) vel.setY(vel.y()*-1);
//    else if(y()>600) vel.setY(vel.y()*-1);

//    if(x()<0) vel.setX(vel.x()*-1);
//    else if(x()>800) vel.setX(vel.x()*-1);
//}

void Player::restrictToEdges()
{
    if(y()<0) loc.setY(0);
    else if(y()>600) loc.setY(600);

    if(x()<0) loc.setX(0);
    else if(x()>800) loc.setX(800);
}

QRectF Player::boundingRect() const
{
    return rect;
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush b((colour ));
    b.setStyle(Qt::BrushStyle::Dense1Pattern);
    painter->setBrush(b);
    painter->drawEllipse(this->boundingRect());
}

Player::~Player()
{
    qDebug() << "~Player()";
}
