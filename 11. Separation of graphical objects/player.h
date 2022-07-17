#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsItem>
#include <QPainter>
#include <QVector2D>
class Player: public QGraphicsEllipseItem
{
public:
    Player(std::vector<Player *> *v_agents, QPointF p);
    virtual ~Player();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
    void applyForce(QVector2D& force);
    void advance();
    void performSeparation();
    QVector2D getVelocity();
    QVector2D getLocation();
    void restrictToEdges();
    void setLocation(QVector2D loc_);
private:
    QRectF rect;
    QVector2D loc;
    QVector2D vel;
    QVector2D acc;
    QColor colour;
    QPolygonF triangle;
    std::vector<Player *> *m_v_agents;

};

#endif // PLAYER_H
