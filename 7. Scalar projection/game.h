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
    float findAngleBetween2Lines(const QVector2D &v1, const QVector2D &v2);
    //    float normalize_angle(const float value );
    void calculateScalarProjection(const QVector2D &v1, const QVector2D &v2);
    void mouseMoveEvent(QGraphicsSceneMouseEvent  *event);
private:
    //    Player* player = nullptr;
//    QGraphicsRectItem* target = nullptr;
    QGraphicsView* m_view = nullptr;
    QOpenGLWidget* gl = nullptr;


    QGraphicsLineItem* baseLine_Red;
    QGraphicsLineItem* myCustomLine_Green;
    QGraphicsLineItem* scalarProjectionLine_yellow;
    QGraphicsLineItem* lineConnectingScalProAndCustomLine;
    QVector2D v1;
    QVector2D v2;
    QVector2D originPoint;
    QLabel* labelAngle = nullptr;
    QLabel* labelDescription = nullptr;

};

#endif // GAME_H
