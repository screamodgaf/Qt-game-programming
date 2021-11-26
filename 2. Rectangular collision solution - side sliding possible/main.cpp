#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include "item.h"
#include "player.h"
#include <QDebug>
#include "game.h"

int main(int argc, char *argv[])
{
#ifdef Q_OS_ANDROID
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication a(argc, argv);
    QGraphicsScene* scene = new QGraphicsScene; ///The QGraphicsScene class serves as a container for QGraphicsItems. It also provides functionality that lets you efficiently determine the location of items as well as determining which items are visible within an arbitrary area on the scene.
//    scene->setSceneRect(-300, -300, 800, 600 );  //glitch disappears when sceneRect is smaller than View !!
//  scene->setSceneRect(-3300, -3300, 3800, 3600 );


    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    QGraphicsView* view = new QGraphicsView(scene); ///To be able to view the scene (which is a container for QGraphicsItems), we must also create a QGraphicsView widget. The QGraphicsView class visualizes the contents of a scene in a scrollable viewport.
    view->setRenderHint(QPainter::Antialiasing);
    QBrush brush(Qt::black);

    view->setBackgroundBrush(brush);
//   view->setBackgroundBrush(QPixmap("D:/E/22.jpg"));
//    view.setBackgroundBrush(QPixmap(":/images/cheese.jpg")); ///The image used for the background is stored as a binary file in the application's executable using Qt's resource system. The QPixmap constructor accepts both file names that refer to actual files on disk and file names that refer to the application's embedded resources.
    view->setCacheMode(QGraphicsView::CacheBackground); ///Then we set the cache mode; QGraphicsView can cache pre-rendered content in a pixmap, which is then drawn onto the viewport. The purpose of such caching is to speed up the total rendering time for areas that are slow to render, for example: texture, gradient, and alpha blended backgrounds. The CacheMode property holds which parts of the view are cached, and the CacheBackground flag enables caching of the view's background.
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
//    view.setDragMode(QGraphicsView::ScrollHandDrag); ///By setting the dragMode property, we define what should happen when the user clicks on the scene background and drags the mouse. The ScrollHandDrag flag makes the cursor change into a pointing hand, and dragging the mouse around will scroll the scrollbars.
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "game2D"));
//    view->resize(810, 610);
    view->resize(810, 610);
    view->show();

    ///main class:
    Game game(scene, view);

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, scene, &QGraphicsScene::advance); ///Finally, we create a QTimer and connect its timeout() signal to the advance() slot of the scene. Every time the timer fires, the scene will advance one frame. We then tell the timer to fire every 1000/33 milliseconds. This will give us a frame rate of 30 frames a second



    timer.start(1000 / 60);



    a.exec();
}
