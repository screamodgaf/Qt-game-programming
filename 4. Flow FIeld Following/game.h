#ifndef GAME_H
#define GAME_H
#include "player.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QOpenGLWidget>
#include <QGraphicsRectItem>
#include "flowfield.h"

class Game : public QGraphicsScene
{
public:
    Game();
    ~Game();
    void keyPressEvent(QKeyEvent* event);
    void advance();
private:
    float normalize_angle(const float value );
    float map(float value, float start1, float stop1, float start2, float stop2);
private:
    Player* player = nullptr;
    QGraphicsRectItem* target = nullptr;
    QGraphicsView* m_view = nullptr;
    QOpenGLWidget* gl = nullptr;
    FlowField* flowField = nullptr;



};

#endif // GAME_H
