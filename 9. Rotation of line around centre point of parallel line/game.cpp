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
    m_view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform  | QPainter::LosslessImageRendering | QPainter::TextAntialiasing);
    m_view->setViewportUpdateMode(QGraphicsView::NoViewportUpdate );
    m_view->setCacheMode(QGraphicsView::CacheBackground);
    m_view->setBackgroundBrush(Qt::black);
    m_view->show();

    whiteLine = new QGraphicsLineItem;
    whiteLine->setLine(200,200, 600,200);
    QPen whiteLinePen(Qt::white, 5);
    whiteLine->setPen(whiteLinePen);
    this->addItem(whiteLine);
    whiteLine->setTransformOriginPoint(whiteLine->boundingRect().center());


    redLine = new QGraphicsLineItem;
    redLine->setLine(200,300, 600,300);
    QPen redLinePen(Qt::red, 5);
    redLine->setPen(redLinePen);
    this->addItem(redLine);
    redLine->setTransformOriginPoint(redLine->boundingRect().center());

    centrePoint= new QGraphicsEllipseItem;
    centrePoint->setRect(0,0,5,5); //drawing from 0,0
    centrePoint->setPen(redLinePen);
    this->addItem(centrePoint);
    centrePoint->setPos(redLine->line().center());

    rotation =3;

}

void Game::advance()
{
    //        aligneLines();
    update();
}



void Game::aligneLines()
{

    auto a = rotatePointAroundBase(whiteLine->line().p1(), redLine->line().center(), rotation);
    auto b = rotatePointAroundBase(whiteLine->line().p2(), redLine->line().center(), rotation);
    centrePoint->setPos(redLine->line().center());
    whiteLine->setLine(a.x(), a.y(), b.x(), b.y());
}

QPointF Game::rotatePointAroundBase(QPointF point, QPointF base, float angle)
{
    float sin_ = std::sin(angle*M_PI/180);
    float cos_ = std::cos(angle*M_PI/180);
    point -= base;
    QPointF point_rotated;
    point_rotated.setX (point.x() * cos_ - point.y() * sin_);
    point_rotated.setY( point.x() * sin_ + point.y() * cos_);
    point_rotated+=base;
    return point_rotated;
}



void Game::mouseMoveEvent(QGraphicsSceneMouseEvent  *event)
{
    //    mousePoint = QPointF(event->scenePos().x()  ,
    //                         event->scenePos().y() - 15);
    //    pointItem->setPos(mousePoint);
}



void Game::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
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
    case Qt::Key_Q:
        redLine->setRotation(redLine->rotation() - rotation);
        aligneLines();
        break;

    case Qt::Key_W:
        aligneLines();
        redLine->setRotation(redLine->rotation() + rotation);
        break;
    }
    update();
}

Game::~Game()
{
    qDebug() << "~Game";

    delete target;
    target = nullptr;
    m_view->deleteLater();
    m_view = nullptr;
    gl->deleteLater();
    gl = nullptr;
}
