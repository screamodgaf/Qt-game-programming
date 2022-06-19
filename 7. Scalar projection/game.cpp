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

    baseLine_Red = new QGraphicsLineItem;
    myCustomLine_Green = new QGraphicsLineItem;
    scalarProjectionLine_yellow = new QGraphicsLineItem;
    lineConnectingScalProAndCustomLine = new QGraphicsLineItem;
    originPoint = {200,500};
    v1 = {500,500};
    v2 = {500,500};

    baseLine_Red->setLine(originPoint.x(), originPoint.y(), v1.x(), v1.y());
    myCustomLine_Green->setLine(originPoint.x(), originPoint.y(), v2.x(), v2.y());
    scalarProjectionLine_yellow->setLine(originPoint.x(), originPoint.y(), 0, 0);

    QPen p1(Qt::red, 8);
    baseLine_Red->setPen(p1);
    QPen p2(Qt::green, 8);
    myCustomLine_Green->setPen(p2);
    QPen p3(Qt::yellow, 8);
    scalarProjectionLine_yellow->setPen(p3);
    QPen p4(Qt::white, 1);
    lineConnectingScalProAndCustomLine->setPen(p4);


    this->addItem(baseLine_Red);
    this->addItem(myCustomLine_Green);
    this->addItem(scalarProjectionLine_yellow);
    this->addItem(lineConnectingScalProAndCustomLine);


    labelAngle = new QLabel;

    QPalette palette(Qt::white,Qt::black);
    labelAngle->setPalette(palette);
    labelAngle->setAlignment(Qt::AlignCenter);
    QFont font = labelAngle->font();
    font.setPointSize(90);
    font.setBold(true);
    labelAngle->setFont(font);
    labelAngle->setMinimumWidth(1200);
    this->addWidget(labelAngle);

    //description label:
    labelDescription = new QLabel;
    QPalette palette2(Qt::yellow, Qt::black);
    labelDescription->setPalette(palette2);
    labelDescription->setAlignment(Qt::AlignLeft);
    font.setPointSize(30);
    font.setBold(true);
    labelDescription->setFont(font);
    labelDescription->setMinimumWidth(1200);
    labelDescription->setText("scalar projection = |A| cos θ");
    labelDescription->setGeometry( 200,510,100,50);
    this->addWidget(labelDescription);

}


void Game::advance()
{
    findAngleBetween2Lines(v1, v2);
    calculateScalarProjection(v1, v2);

    update();
}

void Game::calculateScalarProjection(const QVector2D& v1, const QVector2D& v2)
{
    QVector2D redVec = v1 - originPoint;
    QVector2D greenVec = v2 - originPoint;

    QVector2D scalarProjectionVec = redVec.normalized();

    //scalarProjection vector is to have the same direction as the red line - as its a shadow cast on the red line
    float dotPr = QVector2D::dotProduct(greenVec, scalarProjectionVec); // dotProduct gives the length of the shadow (scalarProjection vector) cast

    scalarProjectionVec *= dotPr;

    scalarProjectionLine_yellow->setLine(originPoint.x(), originPoint.y(),
                                         scalarProjectionVec.x() + originPoint.x(),
                                         scalarProjectionVec.y() + originPoint.y());

    lineConnectingScalProAndCustomLine->setLine(v2.x(), v2.y(),
                                                scalarProjectionVec.x() + originPoint.x(),
                                                scalarProjectionVec.y() + originPoint.y());


    labelDescription->setGeometry( scalarProjectionVec.x() + originPoint.x()-200
                         ,510,100,50);


}

float Game::findAngleBetween2Lines(const QVector2D& v1, const QVector2D& v2)
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

    labelAngle->setText(QString::number(int(angle)) + "°");

    return angle;
}



void Game::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    v2.setX(event->scenePos().x());
    v2.setY(event->scenePos().y());
    myCustomLine_Green->setLine(originPoint.x(), originPoint.y(), v2.x(), v2.y());
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
//    delete target;
//    target = nullptr;
    labelAngle->deleteLater();
    labelAngle = nullptr;
    labelDescription->deleteLater();
    labelDescription = nullptr;
    delete baseLine_Red;
    baseLine_Red = nullptr;
    delete myCustomLine_Green;
    myCustomLine_Green = nullptr;
    delete scalarProjectionLine_yellow;
    scalarProjectionLine_yellow = nullptr;
    delete lineConnectingScalProAndCustomLine;
    lineConnectingScalProAndCustomLine = nullptr;

    m_view->deleteLater();
    m_view = nullptr;
    gl->deleteLater();
    gl = nullptr;
}
