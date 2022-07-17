#include "game.h"
#include <iostream>
#include <QKeyEvent>

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

    makeAgents(210 );
}


void Game::makeAgents(int n)
{
    for (int i = 0; i < n; ++i) {
        int x = 100+ std::rand() % 200;
        int y = 100+ std::rand() % 200;
        agent = new Player(&v_agents, {static_cast<qreal>(x),
                                       static_cast<qreal>(y)});
        this->addItem(agent);
        v_agents.push_back(agent);
    }
}


float Game::normalize_angle(const float value ) {
    float start = -180.f;
    float end = 180.f;
    float width = end - start   ;
    float offsetValue = value - start ;
    return ( offsetValue - ( floor( offsetValue / width ) * width ) ) + start ;
}

void Game::advance()
{
    for (int i = 0; i < v_agents.size(); ++i) {
        v_agents.at(i)->performSeparation();
        v_agents.at(i)->restrictToEdges();
        v_agents.at(i)->advance();
    }
    update();
}


float Game::map(float value, float start1, float stop1, float start2, float stop2) {
    float result = start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
    return result;
}

void Game::keyPressEvent(QKeyEvent *event)
{
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
    update();
}

void Game::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    v_agents[0]->setLocation({static_cast<float>(event->scenePos().x()),
                              static_cast<float>(event->scenePos().y())});
    qDebug() << "event: " << event->scenePos();
}

Game::~Game()
{
    qDebug() << "~Game";
    delete agent;
    agent = nullptr;

    m_view->deleteLater();
    m_view = nullptr;
    gl->deleteLater();
    gl = nullptr;
}
