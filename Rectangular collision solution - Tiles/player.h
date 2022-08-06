#ifndef PLAYER_H
#define PLAYER_H

#include "item.h"
#include <QGraphicsBlurEffect>
#include <memory>
#include <QGraphicsView>
#include <QVector2D>
class Player : public QGraphicsItem
{
public:
    Player();
    ~Player();
    void passView(QGraphicsView* view);
    void advance(std::chrono::duration<float> &duration)  ;
protected:

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    QRectF boundingRect() const override; //pure virtual public function - When writing a custom graphics item, you must implement QGraphicsItem's two pure virtual public functions: boundingRect(), which returns an estimate of the area painted by the item, and paint(), which implements the actual painting. In addition, we reimplement the shape() and advance().
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, //pure virtual public function
               QWidget *widget) override;

private:
    void checkCollisions();
private:
    float speed;
    QColor color;
    bool is_moving_left ;
    bool is_moving_right;
    bool is_moving_up   ;
    bool is_moving_down ;

    QRectF rect;

    QList<QGraphicsItem*> sceneItems;
    std::vector<QGraphicsItem*> v_itemsInCollisionWithPlayer;

    QGraphicsView* m_view = nullptr;
    float d ; //delta





};

#endif // PLAYER_H
