#include "player.h"
#include <iostream>
#include <QDebug>
#include <QKeyEvent>
Player::Player()
{
    speed = 4;
    is_moving_left  = false;
    is_moving_right = false;
    is_moving_up    = false;
    is_moving_down  = false;
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

void Player::advance(int step)
{
    if (!step) return;

    if(is_moving_up)
        this->moveBy(0,-speed);
    if(is_moving_down)
        this->moveBy(0,speed);
    if(is_moving_left)
        this->moveBy(-speed, 0);
    if(is_moving_right)
        this->moveBy(speed,0);
}
