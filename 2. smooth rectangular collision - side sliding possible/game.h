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
class Game: public QObject
{
    Q_OBJECT
public:
    explicit Game(QGraphicsScene* scene, QGraphicsView* view, QObject *parent = nullptr);

    ~Game();
public slots:
    void frameHandler();
private:
    QGraphicsScene* m_scene;
    QGraphicsView* m_view;
    Player player;
    Item testRect;
    Item testRect2;
    Item testRect3;
    QGraphicsTextItem* text;
    QLabel* fpsLabel;
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end ;
    std::chrono::duration<float> duration;
};

#endif // GAME_H
