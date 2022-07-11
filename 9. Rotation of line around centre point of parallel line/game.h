#ifndef GAME_H
#define GAME_H
//#include "player.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QOpenGLWidget>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QLCDNumber>
#include <QGraphicsProxyWidget>
#include <QLabel>
class Game : public QGraphicsScene
{
public:
    Game();
    ~Game();
    void keyPressEvent(QKeyEvent* event);
    void advance();

private:
    QPointF rotatePointAroundBase(QPointF point, QPointF base, float angle);
    void aligneLines();
    void mouseMoveEvent(QGraphicsSceneMouseEvent  *event);
private:

    QGraphicsRectItem* target = nullptr;
    QGraphicsView* m_view = nullptr;
    QOpenGLWidget* gl = nullptr;
    QVector2D v1;
    QVector2D v2;
    QGraphicsLineItem* whiteLine;
    QGraphicsLineItem* redLine;
    float rotation;
    QPointF mousePoint;
    QGraphicsEllipseItem* centrePoint;
};

#endif // GAME_H
