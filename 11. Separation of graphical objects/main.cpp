#include <QApplication>
#include "game.h"
#include <QTimer>

///based on https://natureofcode.com/book/chapter-6-autonomous-agents/

int main(int argc, char *argv[])
{
    std::srand(std::time(nullptr));

    QApplication a(argc, argv);
    Game g;
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &g, &Game::advance);
    timer.start(1000/60); ///60 frames a second
    return a.exec();
}
