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
    speed = 225.f;
    is_moving_left  = false;
    is_moving_right = false;
    is_moving_up    = false;
    is_moving_down  = false;

    rect.setSize(QSize(100.f,100.f));

    m_blurEffect = new QGraphicsBlurEffect;
    m_blurEffect->setBlurRadius(0);
    this->setGraphicsEffect(m_blurEffect);
    m_blurEffect->setEnabled(false);

    old_x = this->x();
    old_y = this->y();

    is_draw = true;
    yxswitch = 0;
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
    m_painter = painter;
    //    if(is_draw == false){
    //        m_painter = preCollisionPainter; //dont draw when collision occurs
    //        return;
    //    }else
    //    {
    //        preCollisionPainter = m_painter;
    //    }


    m_painter->setBrush(color);
    m_painter->drawRect(0, 0, 100, 100);
    m_painter->setRenderHint(QPainter::Antialiasing);
}




bool Player::checkCollisions()
{
    //    preCollisionPainter = m_painter;
    //    for (int i = 0; i < v_itemsInCollisionWithPlayer.size(); ++i) {
    //        ///items that in the previous iteration were colliging with the player - items remaining in collision
    //        v_itemsInCollisionWithPlayer[i]->graphicsEffect()->setEnabled(false);
    //        v_itemsInCollisionWithPlayer.erase(v_itemsInCollisionWithPlayer.begin()+i); //so the vector size doesnt rise at infinitum
    //    }

    sceneItems = collidingItems(); ///get items in collision | Returns a list of all items that collide with this item.




    if(sceneItems.size() == 0) { ///No collisions taking place
        //ressolvig collision
        //        old_x = this->x(); ///set old position to current values, as there is no collision now
        //        old_y = this->y();
        //        oldScene_x = scene()->sceneRect().x();
        //        oldScene_y = scene()->sceneRect().y();
        //        //ressolvig collision end

        //        m_blurEffect->setEnabled(false);
        return false;
    }

    //    std::cout << "collision" << "\n";
    //    m_blurEffect->setEnabled(true); ///enable players effects

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
        //        std::cout << "vecBetweenCentres: " << vecBetweenCentres.x() << " " << vecBetweenCentres.y()<< "\n";
        //        qreal vecBetweenCentresX = thisCentre.x() - colCentre.x();
        //        qreal vecBetweenCentresY = thisCentre.y() - colCentre.y();
        //        std::cout << "rectCentre: " << thisCentre.y()  << "\n";
        //        std::cout << "colRectCentre: " << colCentre.y()<< "\n";

        ///check if the x vector is longer than the y vector:
        if(vecBetweenCentres.y() * vecBetweenCentres.y() > vecBetweenCentres.x() * vecBetweenCentres.x()) ///if the y vector is longer than x:
        {
            ///check direction of the vector, is it pointing down (down movement):
            if(vecBetweenCentres.y() > 0){
                ///set this rect y to the bottom of the colliding rect:
                this->setY(i->pos().y() + i->boundingRect().height());
            }
            else{ ///if y vector is pointing up (up movement):
                this->setY(i->y() - i->boundingRect().height());
            }
        }

        else ///the x vector is larger than the y
        {
            if(vecBetweenCentres.x() >0){
                this->setX(i->pos().x() +this->rect.width() );///right movement
            }else{
                this->setX(i->pos().x()  - this->rect.width() ); ///left movement |  -0.1 is not needed, it only causes shaking
            }

        }

        //        i->graphicsEffect()->setEnabled(true);
        //        v_itemsInCollisionWithPlayer.push_back(i); ///put the items in collision with player into a vector to preservee their state for the next iteration*/

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

    d=0; /// setting delta to 0 is crucial to avoiding some of the remaining shaking of the player !!! this way when there is collision and x or y is set to side of the collider - player (while the arrow keys are still pressed) cannot longer push against the collider - its speed is set to 0 (by multiplication by 0) and with when i press the arrows another time there was no shaking anyway
    return true;
}

/*
 * player is to cause scene to move with it when its placed less than 200 on x near the view border
 */

//why 2 times update needed
void Player::advance(int step)
{

    //    if (!step) return;


    if(checkCollisions()==true){   //we dont want to move the scene if there is a collision
        return;
    }
    //    is_draw = true;
    m_view->centerOn(this); /// shouldnt be past the below moving sets - othewrwise shakes
    if(d>0.09) d =0.001; ///for FPS count - to get frame ticks Game classes connects "&QGraphicsScene::changed" with "this, &Game::frameHandler" - so it calls frameHandler when somethign actually FIRST changes in the in the scene, thus to avoid getting suddent movement of speed value 200, i artificially set duration to 0.001 to limit speed in the first frame

    if(is_moving_up){
        this->moveBy(0,-speed * d); ///d = deltatime
        //        r.translate(0,-speed * d);
    }
    else if(is_moving_down){
        this->moveBy(0,speed * d);
        //        r.translate(0,speed * d);
    }
    if(is_moving_left){
        this->moveBy(-speed * d, 0);
        //        r.translate(-speed * d, 0);
    }
    else if(is_moving_right){
        this->moveBy(speed * d, 0);
        //        r.translate(speed * d, 0);
    }


    //    auto r = scene()->sceneRect();
    //    std::cout << "scene->x(): " << r.x() << "\n";
    //    std::cout << "scene->y(): " << r.y() << "\n";
    //    QPointF point(x(), y());
    //    if(r.x()< mapToScene(point).x()+200 ||
    //       r.x()< mapToScene(point).x()-20+scene()->width()
    //            )
    //    {

    //this->setPos(scene()->width()/2, scene()->height()/2);
    //        r.setX(mapToScene(point).x());
    //        r.setY(mapToScene(point).y());
    //        scene()->setSceneRect(r);
    //    }

    //    m_view->centerOn(this);


    //    std::cout << "this->x(): " << this->x() << "\n";
    //    std::cout << "this->y(): " << this->y() << "\n";
    //    if(checkCollisions()==true){
    //        is_draw = false;
    //        m_painter = preCollisionPainter;
    //        return;
    //    }
    //    else
    //        preCollisionPainter = m_painter;
    //    is_draw = true;
    std::cout << "-----------------"  << "\n";
}


void Player::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())  {
    case Qt::Key_Left :
        is_moving_left = true;
        break;
    case Qt::Key_Right :
        is_moving_right = true;
        break;
    case Qt::Key_Up :
        is_moving_up = true;
        break;
    case Qt::Key_Down :
        is_moving_down = true;
        break;
    }
}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key())  {
    case Qt::Key_Left :
        is_moving_left = false;
        break;
    case Qt::Key_Right :
        is_moving_right = false;
        break;
    case Qt::Key_Up :
        is_moving_up = false;
        break;
    case Qt::Key_Down :
        is_moving_down = false;
        break;
    }
}


void Player::passView(QGraphicsView* view)
{
    m_view = view;
}

void Player::passDelta(std::chrono::duration<float> &duration)
{
    d = duration.count() ;
}

Player::~Player()
{
    m_blurEffect->deleteLater();
}
