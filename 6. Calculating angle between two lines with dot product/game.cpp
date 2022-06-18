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

    line1 = new QGraphicsLineItem;
    line2 = new QGraphicsLineItem;

    originPoint = {200,300};
    v1 = {500,300};
    v2 = {500,300};

    line1->setLine(originPoint.x(), originPoint.y(), v1.x(), v1.y());
    line2->setLine(originPoint.x(), originPoint.y(), v2.x(), v2.y());

    QPen p1(Qt::red, 8);
    line1->setPen(p1);
    QPen p2(Qt::green, 8);
    line2->setPen(p2);

    this->addItem(line1);
    this->addItem(line2);

    label = new QLabel;

    QPalette p(Qt::white,Qt::black);
    label->setPalette(p);
    label->setAlignment(Qt::AlignCenter);
    QFont font = label->font();
    font.setPointSize(90);
    font.setBold(true);
    label->setFont(font);
    label->setMinimumWidth(1200);

    this->addWidget(label);
}


void Game::advance()
{
    findAngleBetween2Lines(v1, v2);
    update();
}

float Game::findAngleBetween2Lines(QVector2D& v1, QVector2D& v2)
{
    float v1x = v1.x() - originPoint.x();
    float v1y = v1.y() - originPoint.y();

    float v2x = v2.x() - originPoint.x();
    float v2y = v2.y() - originPoint.y();

    float dotPr = QVector2D::dotProduct({v1x, v1y}, {v2x, v2y});

    float v1_magnitude = std::sqrt(v1x * v1x + v1y * v1y);
    float v2_magnitude = std::sqrt(v2x * v2x + v2y * v2y);

    float angle = std::acos(dotPr/ (v1_magnitude * v2_magnitude ));
    angle *= 180 / M_PI;

    if (v2y>0)  angle = 360 -angle ;

    label->setText(QString::number(int(angle)) + "°");

    return angle;
}

void Game::mouseMoveEvent(QGraphicsSceneMouseEvent  *event)
{
    v2.setX(event->scenePos().x());
    v2.setY(event->scenePos().y());
    line2->setLine(originPoint.x(), originPoint.y(), v2.x(), v2.y());
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
//    delete player;
//    player = nullptr;
    delete target;
    target = nullptr;
    m_view->deleteLater();
    m_view = nullptr;
    gl->deleteLater();
    gl = nullptr;
}
