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
    m_view->setBackgroundBrush(Qt::black);
    m_view->show();

    road = new Road();
    player = new Player(road, this, {100,100});
    this->addItem(road);
    this->addItem(player);



}


void Game::advance()
{

    //    QVector2D push(1,0);
    //    player->applyForce(push);
    player->advance();
    m_view->centerOn(player);
    road->advance(1);


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
//        target->moveBy(-7,0);
//        break;
//    case Qt::Key_Right:
//        target->moveBy(7,0);
//        break;
//    case Qt::Key_Up:
//        target->moveBy(0, -7);
//        break;
//    case Qt::Key_Down:
//        target->moveBy(0, 7);
//        break;
//    case Qt::Key_Q:
//        target->setRotation(target->rotation() -3);
//        break;
//    case Qt::Key_W:
//        target->setRotation(target->rotation() +3);
//        break;
//    }
//    update();
//}

Game::~Game()
{
    qDebug() << "~Game";
        delete player;
        player = nullptr;
        delete road;
        road = nullptr;


    m_view->deleteLater();
    m_view = nullptr;
    gl->deleteLater();
    gl = nullptr;
    qDebug() << "~Game2";
}
