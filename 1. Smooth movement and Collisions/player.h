#ifndef PLAYER_H
#define PLAYER_H

#include "item.h"

class Player : public Item
{
public:
    Player();
protected:
    void advance(int step) override;
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    int speed;
    bool is_moving_left ;
    bool is_moving_right;
    bool is_moving_up   ;
    bool is_moving_down ;
};

#endif // PLAYER_H
