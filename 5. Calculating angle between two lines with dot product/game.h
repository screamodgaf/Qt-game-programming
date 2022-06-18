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
#include <QPointF>
class Game : public QGraphicsScene
{
public:
    Game();
    ~Game();
//    void keyPressEvent(QKeyEvent* event);
    void advance();

private:
    float findAngleBetween2Lines(QVector2D &v1, QVector2D &v2);
//    float normalize_angle(const float value );
    void mouseMoveEvent(QGraphicsSceneMouseEvent  *event);
private:
//    Player* player = nullptr;
    QGraphicsRectItem* target = nullptr;
    QGraphicsView* m_view = nullptr;
    QOpenGLWidget* gl = nullptr;


    QGraphicsLineItem* line1;
    QGraphicsLineItem* line2;
    QVector2D v1;
    QVector2D v2;
    QPointF originPoint;
    QLabel* label = nullptr;

};

#endif // GAME_H
