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

    player = new Player;
    player->setPos(200,300);
    player->setZValue(10);
    this->addItem(player);

    target = new QGraphicsRectItem();
    target->setRect(0,0,40,40);
    target->setBrush(Qt::red);
    target->setPos(500,400);
    target->setTransformOriginPoint(target->boundingRect().center());
    target->setFlag(QGraphicsItem::ItemIsFocusable);
    this->addItem(target);
}

float Game::normalize_angle(const float value ) {
    float start = -180.f;
    float end = 180.f;
    float width = end - start   ;
    float offsetValue = value - start ;
    return ( offsetValue - ( floor( offsetValue / width ) * width ) ) + start ;
}

float maxSpeed = 2.f;
float maxForce = 0.01; ///how sharp the turns are

void Game::advance()
{
    //    QVector2D desiredVel = QVector2D(target->pos() - player->pos());
    //    ///setting magnitude to maxSpeed (normalizing to length 1 and scaled by multiplying by maxSpeed)
    //    desiredVel.normalize();
    //    desiredVel *= maxSpeed;
    //    ///Reynolds formula:
    //    QVector2D steering = desiredVel - player->getVelocity();
    //    ///limit force by setting maximum force to maxForce:
    //    steering.normalize();
    //    steering *= maxForce;

    //    player->applyForce(steering);


    m_view->centerOn(target);

    ///Arrive behaviour:
    QVector2D desiredVel = QVector2D(target->pos() - player->pos());
    float distance = desiredVel.length();
    desiredVel.normalize();

    if(distance<400){
        float m = map(distance, 200,450, 0, maxSpeed);
        desiredVel *= m;
    }else{
        desiredVel *= maxSpeed;
    }

    ///Reynolds formula:
    QVector2D steering = desiredVel - player->getVelocity();
    ///limit force by setting maximum force to maxForce:
    steering.normalize();
    steering *= maxForce;

    player->applyForce(steering);


    ///player rotation toward target:
    QVector2D distBetweenPoints(((target->x() + target->boundingRect().width()/2)
                                 - (player->x() + player->boundingRect().width()/2)),

                                (target->y() + target->boundingRect().height()/2)
                                - (player->y() + target->boundingRect().height()/2));

    double rad = std::atan2(distBetweenPoints.y(), distBetweenPoints.x()); //    float rotation = std::atan2(player->y() - target->pos().y(),  player->x() - target->pos().x()) *270.f/M_PI;
    double degrees =  rad* 180.0 /M_PI;
    degrees = normalize_angle(degrees);
    player->setRotation(degrees+270);

    ///call player update method:
    player->advance();
    update();
}

float Game::map(float value, float start1, float stop1, float start2, float stop2) {
    float result = start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
    return result;
}

void Game::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Left:
        target->moveBy(-7,0);
        break;
    case Qt::Key_Right:
        target->moveBy(7,0);
        break;
    case Qt::Key_Up:
        target->moveBy(0, -7);
        break;
    case Qt::Key_Down:
        target->moveBy(0, 7);
        break;
    case Qt::Key_Q:
        target->setRotation(target->rotation() -3);
        break;
    case Qt::Key_W:
        target->setRotation(target->rotation() +3);
        break;
    }
    update();
}

Game::~Game()
{
    qDebug() << "~Game";
    delete player;
    player = nullptr;
    delete target;
    target = nullptr;
    m_view->deleteLater();
    m_view = nullptr;
    gl->deleteLater();
    gl = nullptr;
}
