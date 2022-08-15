#include "maploader.h"
#include <QDebug>

MapLoader::MapLoader()
{
    if(!mImage.load(":/map.bmp"))
        qDebug() << "Map was not loaded";
    qDebug() << "mImage.size().height(): " << mImage.size().height();
    qDebug() << "mImage.size().width(): " << mImage.size().width();
}

std::vector<int> &MapLoader::loadMap()
{
    for (int y = 0; y < mImage.size().height(); ++y) {
        for (int x = 0; x < mImage.size().width(); ++x) { //jiggering of the solid elements is caused by flag n and this +vel prevents it
            QColor c = mImage.pixel(x, y);
            if(c ==  QColor(0, 0,0)){
                v.push_back(1);
            }
            else
               v.push_back(0);
        }
    }

    return v;
}


