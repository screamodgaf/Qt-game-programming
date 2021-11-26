#include "game.h"
#include "player.h"
#include "tiles.h"
#include <iostream>
#include <chrono>

Game::Game(QGraphicsScene* scene, QGraphicsView* view, QObject *parent): QObject(parent), m_scene(scene), m_view(view)
{   
    Tiles tiles;
    tiles.displayTiles(scene, view);

    connect(m_scene, &QGraphicsScene::changed, this, &Game::frameHandler); //for FPS count

    //main character:
    player.setFlag(QGraphicsItem::ItemIsFocusable); ///only one item can respond to keyboard events
    player.setFocus();
    player.passView(view);
    m_scene->addItem(&player);

    ///item for testing collisions
        testRect.setPos(view->mapToScene( 100, 100));
        QColor c= Qt::red;
        testRect.setColour(c);
        m_scene->addItem(&testRect);



    //    auto r = m_scene->sceneRect();
    //    r.translate(310.1,0.1);
    //    m_scene->setSceneRect(r );

    fpsLabel = new QLabel(m_view);
    fpsLabel->setGeometry(5,5, 60, 20); // so not only the first char appears - it must be widened
    fpsLabel->setStyleSheet("QLabel { color : lime; font-size: 15px;}");
    fpsLabel->show();



    start = std::chrono::high_resolution_clock::now(); //
}



void Game::frameHandler()
{
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
//    std::cout << "tick duration: " << duration.count() << "\n";
    start = std::chrono::high_resolution_clock::now();


//    std::cout << "FPS: " <<  1/duration.count()  << "\n"; //1 second =    1000 milliseconds

    player.passDelta(duration);

    fpsLabel->setText("FPS: " + QString::number(int(1/duration.count())));


}

Game::~Game()
{
    m_scene->deleteLater();
}
