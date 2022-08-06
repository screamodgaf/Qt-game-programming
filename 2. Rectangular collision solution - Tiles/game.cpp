#include "game.h"
#include "player.h"
//#include "tiles.h"
#include <iostream>
#include <chrono>
#include "maps.h"
Game::Game()
{
    m_view = new QGraphicsView(this);
    m_view->setSceneRect(QRectF(0,0,8000000, 8000000));

    gl = new QOpenGLWidget(m_view);
    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::OpenGLContextProfile::CompatibilityProfile);
    format.setRenderableType(QSurfaceFormat::OpenGL);

    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(3, 2);
    format.setSwapBehavior(QSurfaceFormat::TripleBuffer);
    format.setSwapInterval(1);
    format.setSamples(4);
    gl->setFormat(format);
    m_view->setViewport(gl);
    //opengl end

    m_view->setScene(this);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "game"));
    m_view->resize(800, 600);
    m_view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform  |
                           QPainter::LosslessImageRendering | QPainter::TextAntialiasing);
    m_view->setViewportUpdateMode(QGraphicsView::NoViewportUpdate );

    m_view->setCacheMode(QGraphicsView::CacheBackground);
    m_view->setBackgroundBrush(Qt::black);
    m_view->show();

    Maps maps;
    maps.displayTiles(this, m_view);

    //main character:
    player = new Player;
    player->setFlag(QGraphicsItem::ItemIsFocusable); ///only one item can respond to keyboard events
    player->setFocus();
    player->passView(m_view);
    this->addItem(player);


    fpsLabel = new QLabel(m_view);
    fpsLabel->setGeometry(5,5, 60, 20); // so not only the first char appears - it must be widened
    fpsLabel->setStyleSheet("QLabel { color : lime; font-size: 15px;}");
    fpsLabel->show();

    timeElapsed = std::chrono::microseconds(0);
    start = std::chrono::high_resolution_clock::now();
}

void Game::advance()
{
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    //    std::cout << "tick duration: " << duration.count() << "\n";
    start = std::chrono::high_resolution_clock::now();

    //    std::cout << "FPS: " <<  1/duration.count()  << "\n"; //1 second =    1000 milliseconds

    fpsLabel->setText("FPS: " + QString::number(int(1/duration.count())));


    ///if framerate is faster than 0.0163463 - wait untill it reaches 0.0163463 by entering while loop; "duration" in the the while loops condition insreases every iteration of the while iteration by the time the while iteration takes
    auto tstart = std::chrono::high_resolution_clock::now();  ///10
    while (duration.count() <  0.016) {   ///60 fps = 16 miliseconds cause 60*16 = 1000 so 0,016  sec = 16 miliseconds
        auto tend = std::chrono::high_resolution_clock::now(); ///20
        duration += tend-tstart; ///20 - 10 = 10 so while iteration took 10 | then we add the while iteration duration to framerate duration
    }

    player->advance(duration);
    m_view->centerOn(player);

    update();
}





Game::~Game()
{
    qDebug() << "~Game";
    delete player;
    player = nullptr;
    m_view->deleteLater();
    m_view = nullptr;
    gl->deleteLater();
    gl = nullptr;
}
