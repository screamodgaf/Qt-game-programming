#include <QApplication>
#include "game.h"
#include <QTimer>
#include <ctime>
#include <cstdlib>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::srand(std::time(0));
    Game g;
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &g, &Game::advance);
    timer.start(1000/60); ///60 frames a second
    return a.exec();
}
