#include <QApplication>
#include "game.h"
#include <QTimer>
#include <ctime>

int main(int argc, char *argv[])
{
    std::srand(time(nullptr));

    QApplication a(argc, argv);
    Game g;
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &g, &Game::advance);
    timer.start(1000/60 ); ///60 frames a second
    return a.exec();
}
