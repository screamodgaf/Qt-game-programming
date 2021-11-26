#include "game.h"
#include "player.h"
#include "tiles.h"
#include <iostream>
#include <chrono>
#include "bitmaps.h"

Game::Game(QGraphicsScene* scene, QGraphicsView* view, QObject *parent): QObject(parent), m_scene(scene), m_view(view)
{   
    Bitmaps bitmaps;
    bitmaps.displayTiles(scene, view);
    //    Tiles tiles;
    //    tiles.displayTiles(scene, view);

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
    //        m_scene->addItem(&testRect);



    //    auto r = m_scene->sceneRect();
    //    r.translate(310.1,0.1);
    //    m_scene->setSceneRect(r );

    fpsLabel = new QLabel(m_view);
    fpsLabel->setGeometry(5,5, 60, 20); // so not only the first char appears - it must be widened
    fpsLabel->setStyleSheet("QLabel { color : lime; font-size: 15px;}");
    fpsLabel->show();


timeElapsed = std::chrono::microseconds(0);
 start = std::chrono::high_resolution_clock::now();
}


bool is_sceneUpdated = false;

void Game::frameHandler()
{
    is_sceneUpdated = true;
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;

    std::cout << "tick duration: " << duration.count() << "\n";
    start = std::chrono::high_resolution_clock::now();


    //    std::cout << "FPS: " <<  1/duration.count()  << "\n"; //1 second =    1000 milliseconds

    fpsLabel->setText("FPS: " + QString::number(int(1/duration.count())));



     ///if framerate is faster than 0.0163463 - wait untill it reaches 0.0163463 by entering while loop; "duration" in the the while loops condition insreases every iteration of the while iteration by the time the while iteration takes
     auto tstart = std::chrono::high_resolution_clock::now();  ///10
     while (duration.count() <  0.016) {   ///60 fps = 16 miliseconds cause 60*16 = 1000 so 0,016  sec = 16 miliseconds
         auto tend = std::chrono::high_resolution_clock::now(); ///20
         duration += tend-tstart; ///20 - 10 = 10 so while iteration took 10 | then we add the while iteration duration to framerate duration
     }

     player.passDelta(duration);
}

Game::~Game()
{
    m_scene->deleteLater();
}
