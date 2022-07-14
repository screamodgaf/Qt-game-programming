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
#include <vector>
class Game : public QGraphicsScene
{
public:
    Game();
    ~Game();
//        void keyPressEvent(QKeyEvent* event);
    void advance();

private:

    //    float normalize_angle(const float value );
    void createMultiplePointRoad();
    void mouseMoveEvent(QGraphicsSceneMouseEvent  *event);
private:
    //    Player* player = nullptr;

    QGraphicsView* m_view = nullptr;
    QOpenGLWidget* gl = nullptr;

    Player* player = nullptr;

//    std::vector<Road*> v_Road;
    std::vector<QPointF> v_roadPoints;
    Road* road1;
    Road* road2;
    Road* road3;
    Road* road4;
    Road* road5;
    Road* road6;
    Road* road7;
};

#endif // GAME_H
