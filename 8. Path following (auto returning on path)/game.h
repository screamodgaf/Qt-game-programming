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
#include "road.h"
#include "player.h"

class Game : public QGraphicsScene
{
public:
    Game();
    ~Game();
    //    void keyPressEvent(QKeyEvent* event);
    void advance();

private:

    //    float normalize_angle(const float value );

    void mouseMoveEvent(QGraphicsSceneMouseEvent  *event);
private:
    //    Player* player = nullptr;

    QGraphicsView* m_view = nullptr;
    QOpenGLWidget* gl = nullptr;

    Player* player = nullptr;
    Road* road = nullptr;

};

#endif // GAME_H
