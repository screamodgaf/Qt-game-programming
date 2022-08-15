#ifndef GAME_H
#define GAME_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include <memory>
#include <QTime>
#include <QObject>
#include <QLabel>
#include <QElapsedTimer>
#include <QOpenGLWidget>
#include <QGraphicsSceneMouseEvent>
#include "map.h"
class Game : public QGraphicsScene
{
public:
    Game();
    void advance();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent  *event);
    ~Game();
public slots:
private:
    QGraphicsTextItem* text;
    QLabel* fpsLabel;
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end ;
    std::chrono::duration<float> duration, timeElapsed;
    Map* map = nullptr;
private:
    QGraphicsView* m_view = nullptr;
    QOpenGLWidget* gl = nullptr;
};

#endif // GAME_H
