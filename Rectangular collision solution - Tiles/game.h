#ifndef GAME_H
#define GAME_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include <memory>
#include "item.h"
#include "player.h"
#include <QTime>
#include <QObject>
#include <QLabel>
#include <QElapsedTimer>
#include <QOpenGLWidget>
class Game : public QGraphicsScene
{
public:
    Game();
    void advance();
    ~Game();
public slots:
private:
    Player* player;
    QGraphicsTextItem* text;
    QLabel* fpsLabel;
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end ;
    std::chrono::duration<float> duration, timeElapsed;
private:
    QGraphicsView* m_view = nullptr;
    QOpenGLWidget* gl = nullptr;
};

#endif // GAME_H
