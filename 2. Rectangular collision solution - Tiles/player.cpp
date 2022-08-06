#include "player.h"
#include <iostream>
#include <QDebug>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QGraphicsEffect>
#include <vector>

Player::Player()
    : color(Qt::green)
{
    speed = 195.f;
    is_moving_left  = false;
    is_moving_right = false;
    is_moving_up    = false;
    is_moving_down  = false;

    rect.setSize(QSize(80.f,80.f));




}

QRectF Player::boundingRect() const
{
    return rect;
}

QPainterPath Player::shape() const
{
    //not in use yet
    QPainterPath path;
    path.addRect(rect);
    return path;
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //    m_painter = painter;
    //    if(is_draw == false){
    //        m_painter = preCollisionPainter; //dont draw when collision occurs
    //        return;
    //    }else
    //    {
    //        preCollisionPainter = m_painter;
    //    }

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(color);
    painter->drawRect(0, 0, 80, 80);
}




void Player::checkCollisions()
{

    sceneItems = collidingItems(); ///get items in collision | Returns a list of all items that collide with this item.


    if(sceneItems.size() == 0) { ///No collisions taking place
        return;
    }

    // collisions taking place:
    for (auto& i : sceneItems) { ///checking which items the current item is colliding with

        ///calculate the distance between 2 centres:
        qreal centreX = this->x()+ (this->rect.width()/2);
        qreal centreY = this->y()+ (this->rect.height()/2);
        QPointF thisCentre = {centreX, centreY};

        qreal colcentreX = i->x()+ (i->boundingRect().width()/2);
        qreal colcentreY = i->y()+ (i->boundingRect().height()/2);
        QPointF colCentre = {colcentreX, colcentreY};

        QPointF vecBetweenCentres = thisCentre - colCentre;
        //        qreal vecBetweenCentresX = thisCentre.x() - colCentre.x();
        //        qreal vecBetweenCentresY = thisCentre.y() - colCentre.y();


        ///check if the x vector is longer than the y vector:
        if(vecBetweenCentres.y() * vecBetweenCentres.y() > vecBetweenCentres.x() * vecBetweenCentres.x()) ///if the y vector is longer than x:
        {
            ///check direction of the vector, is it pointing down (down movement):
            if(vecBetweenCentres.y() > 0){
                ///set this rect y to the bottom of the colliding rect:
                this->setY(i->y() + i->boundingRect().height());
            }
            else{ ///if y vector is pointing up (up movement):
                this->setY(i->y() - i->boundingRect().height());
            }
        }

        ///if - else - cant be (vecBetweenCentres.y() * vecBetweenCentres.y()== vecBetweenCentres.x() * vecBetweenCentres.x()) - cause sliding doesnt work!!!
        else if(vecBetweenCentres.y() * vecBetweenCentres.y() < vecBetweenCentres.x() * vecBetweenCentres.x()) ///the x vector is larger than the y
        {
            if(vecBetweenCentres.x() > 0){
                this->setX(i->x() + this->boundingRect().width() );///right movement
            }else
            {
                this->setX(i->x()  - this->boundingRect().width() ); ///left movement |  -0.1 is not needed, it only causes shaking
            }

        }


        ///resolving collisions:
        //https://gamedev.stackexchange.com/questions/69339/2d-aabbs-and-resolving-multiple-collisions
        //        auto r = scene()->sceneRect();

        //        if(yxswitch){ //switch order of moving x y so edge slide is possible in collision with things
        //            this->setPos(this->x(), old_y);///restore y and see if still in collision

        //            if(i->collidesWithItem(this))  ///if still collides - restore x
        //                this->setPos(old_x, this->y());

        //            yxswitch =0;
        //        }
        //        else {
        //            this->setPos(old_x, this->y());///restore y and see if still in collision
        //            if(i->collidesWithItem(this))  ///if still collides - restore x
        //                this->setPos(this->x(), old_y);
        //            yxswitch =1;

        //        }
        //        std::cout << "yxswitch: " << yxswitch << "\n";
    } // end for

    /*  d=0;*/ /// setting delta to 0 is crucial to avoiding some of the remaining shaking of the player !!! this way when there is collision and x or y is set to side of the collider - player (while the arrow keys are still pressed) cannot longer push against the collider - its speed is set to 0 (by multiplication by 0) and with when i press the arrows another time there was no shaking anyway

}

/*
 * player is to cause scene to move with it when its placed less than 200 on x near the view border
 */

//why 2 times update needed
void Player::advance(std::chrono::duration<float> &duration)
{
    d = duration.count() ;

    float _moveby = speed * d;

    if(is_moving_up){
        this->moveBy(0,-_moveby); ///d = deltatime
    }
    else if(is_moving_down){
        this->moveBy(0,_moveby);
    }

    if(is_moving_left){
        this->moveBy(-_moveby, 0);
    }
    else if(is_moving_right){
        this->moveBy(_moveby, 0);
    }

    checkCollisions();   ///we dont want to move the scene if there is a collision


}


void Player::keyPressEvent(QKeyEvent *event)
{

    switch(event->key())  {
    case Qt::Key_Up :
        is_moving_up = true;
        break;
    case Qt::Key_Down :
        is_moving_down = true;
        break;
    case Qt::Key_Left :
        is_moving_left = true;
        break;
    case Qt::Key_Right :
        is_moving_right = true;
        break;
    }

}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key())  {
    case Qt::Key_Up :
        is_moving_up = false;
        break;
    case Qt::Key_Down :
        is_moving_down = false;
        break;
    case Qt::Key_Left :
        is_moving_left = false;
        break;
    case Qt::Key_Right :
        is_moving_right = false;
        break;
    }

}


void Player::passView(QGraphicsView* view)
{
    m_view = view;
}

Player::~Player()
{

}
