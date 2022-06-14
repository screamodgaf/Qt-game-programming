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
    line1->setLine(200,300, 600,300);
    line2->setLine(200,300, 600,400);

    QPen p1(Qt::red, 8);
    line1->setPen(p1);
    QPen p2(Qt::green, 8);
    line2->setPen(p2);

    this->addItem(line1);
    this->addItem(line2);

    label = new QLabel;
//    label->setFixedSize(100,100);
//    label->setMinimumSize(100,100);
//    QFont f( 50, QFont::Bold);
//    label->setFont(f);

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
    findAngleBetween2Lines(line1, line2);
    update();
}

float Game::findAngleBetween2Lines(QGraphicsLineItem* line1, QGraphicsLineItem* line2)
{
    //line1:
    QPointF p1 = {line1->line().x1(), line1->line().y1()}; //start
    QPointF p2 = {line1->line().x2(), line1->line().y2()}; //end
    //line2:
    QPointF p3 = {line2->line().x1(), line2->line().y1()}; //start
    QPointF p4 = {line2->line().x2(), line2->line().y2()}; //end


    float angle1 = atan2(p1.y() - p2.y(), p1.x() - p2.x());
    float angle2 = atan2(p3.y() - p4.y(), p3.x() - p4.x());
    float resultAngle = (angle2-angle1) * 180 / M_PI;
    if (resultAngle<0)  resultAngle+=360;

    label->setText(QString::number(int(resultAngle)) + "°");
    std::cout << "angle: " << resultAngle << "\n";

}

void Game::mouseMoveEvent(QGraphicsSceneMouseEvent  *event)
{
    line2->setLine(200, 300, event->scenePos().x(), event->scenePos().y());
}

float Game::normalize_angle(const float value ) {
    float start = 0.f;
    float end = 360.f;
    float width = end - start   ;
    float offsetValue = value - start ;
    return ( offsetValue - ( floor( offsetValue / width ) * width ) ) + start ;
}

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
