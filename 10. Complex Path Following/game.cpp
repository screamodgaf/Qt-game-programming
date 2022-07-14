#include "game.h"
#include <iostream>
#include <QKeyEvent>
#include <cmath>
#include <QPalette>

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
    m_view->setBackgroundBrush(QColor(9,150,0));
    m_view->show();

    createMultiplePointRoad();
    player = new Player(v_roadPoints, this, {100,100});
    this->addItem(player);



    //m_view->showFullScreen();

}

void Game::createMultiplePointRoad()
{
    v_roadPoints.push_back({200, 100});
    v_roadPoints.push_back({1000, 100});
    v_roadPoints.push_back({1200, 400});
    v_roadPoints.push_back({1000, 800});
    v_roadPoints.push_back({200, 800});
    v_roadPoints.push_back({100, 400});
    v_roadPoints.push_back({200, 100});
//    v_roadPoints.push_back({ 10, 1800});

    road1 = new Road(v_roadPoints[0], v_roadPoints[1]);
    road2 = new Road(v_roadPoints[1], v_roadPoints[2]);
    road3 = new Road(v_roadPoints[2], v_roadPoints[3]);
    road4 = new Road(v_roadPoints[3], v_roadPoints[4]);
    road5 = new Road(v_roadPoints[4], v_roadPoints[5]);
    road6 = new Road(v_roadPoints[5], v_roadPoints[6]);
//    road7 = new Road(v_roadPoints[6], v_roadPoints[7]);

    this->addItem(road1);
    this->addItem(road2);
    this->addItem(road3);
    this->addItem(road4);
    this->addItem(road5);
    this->addItem(road6);
//    this->addItem(road7);

}

void Game::advance()
{

    //    QVector2D push(1,0);
    //    player->applyForce(push);
    player->advance();
    m_view->centerOn(player);



    //    road->update( );

    //       qDebug() << "road->boundingRect(): " << road->boundingRect();
    update();


}



void Game::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //    v2.setX(event->scenePos().x());
    //    v2.setY(event->scenePos().y());
    //    myCustomLine_Green->setLine(originPoint.x(), originPoint.y(), v2.x(), v2.y());
}

//float Game::normalize_angle(const float value ) {
//    float start = 0.f;
//    float end = 360.f;
//    float width = end - start   ;
//    float offsetValue = value - start ;
//    return ( offsetValue - ( floor( offsetValue / width ) * width ) ) + start ;
//}

//void Game::keyPressEvent(QKeyEvent *event)
//{
//    switch(event->key()){
//    case Qt::Key_Left:
//        player->moveBy(-17,0);
//        break;
//    case Qt::Key_Right:
//        player->moveBy(17,0);
//        break;
//    case Qt::Key_Up:
//        player->moveBy(0, -17);
//        break;
//    case Qt::Key_Down:
//        player->moveBy(0, 17);
//        break;
//    case Qt::Key_Q:
//        player->setRotation(player->rotation() -3);
//        break;
//    case Qt::Key_W:
//        player->setRotation(player->rotation() +3);
//        break;
//    }
//    update();
//}

Game::~Game()
{
    qDebug() << "~Game";
    delete player;
    player = nullptr;
    delete road1;
    road1= nullptr;
    delete road2;
    road2= nullptr;
    delete road2;
    road3= nullptr;
    delete road3;
    road4= nullptr;
    delete road4;

    m_view->deleteLater();
    m_view = nullptr;
    gl->deleteLater();
    gl = nullptr;
    qDebug() << "~Game2";
}
