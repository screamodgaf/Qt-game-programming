#ifndef GAME_H
#define GAME_H
#include "player.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QOpenGLWidget>
#include <QGraphicsRectItem>
#include <vector>
#include <QGraphicsSceneMouseEvent>
class Game : public QGraphicsScene
{
public:
    Game();
    ~Game();
    void keyPressEvent(QKeyEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void advance();
    void makeAgents(int n);
private:
    float normalize_angle(const float value );
    float map(float value, float start1, float stop1, float start2, float stop2);
private:
    Player* agent = nullptr;

    QGraphicsView* m_view = nullptr;
    QOpenGLWidget* gl = nullptr;
    std::vector<Player*> v_agents;

};

#endif // GAME_H
