#include <QApplication>
#include "game.h"
#include <QTimer>

///based on https://www.red3d.com/cwr/steer/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game g;
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &g, &Game::advance);
    timer.start(1000/60); ///60 frames a second
    return a.exec();
}
