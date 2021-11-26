#ifndef PLAYER_H
#define PLAYER_H

#include "item.h"
#include <QGraphicsBlurEffect>
#include <memory>
#include <QGraphicsView>
class Player : public QGraphicsItem
{
public:
    Player();
    ~Player();
    void passView(QGraphicsView* view);
    void passDelta(std::chrono::duration<float>& duration);
protected:
    void advance(int step) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    QRectF boundingRect() const override; //pure virtual public function - When writing a custom graphics item, you must implement QGraphicsItem's two pure virtual public functions: boundingRect(), which returns an estimate of the area painted by the item, and paint(), which implements the actual painting. In addition, we reimplement the shape() and advance().
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, //pure virtual public function
               QWidget *widget) override;

private:
    bool checkCollisions();
private:
    float speed;
    QColor color;
    bool is_moving_left ;
    bool is_moving_right;
    bool is_moving_up   ;
    bool is_moving_down ;

    QRectF rect;
    QPainter* m_painter = nullptr;
    QGraphicsBlurEffect* m_blurEffect = nullptr;


    QList<QGraphicsItem*> sceneItems;
    std::vector<QGraphicsItem*> v_itemsInCollisionWithPlayer;

    QGraphicsView* m_view ;
    float d ; //delta


    qreal old_x;
    qreal old_y;
    qreal oldScene_x;
    qreal oldScene_y;

    bool is_draw;
    bool is_sceneChanged;

    QPainter *preCollisionPainter = nullptr;
};

#endif // PLAYER_H
