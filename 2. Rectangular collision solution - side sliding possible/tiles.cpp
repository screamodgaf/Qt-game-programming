#include "tiles.h"
#include <iostream>
#include "item.h"
int map[225] =
{
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,2,0,0,0,0,2,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
    2,0,0,0,0,0,0,1,1,1,2,2,2,0,0,
    0,0,0,0,0,0,0,1,1,0,0,0,0,0,2,
    0,0,0,0,0,0,1,1,1,0,0,0,1,0,2,
    2,0,0,0,0,0,0,0,0,0,0,0,1,0,2,
    0,0,0,0,0,0,1,1,1,1,1,1,1,0,2,
    0,0,0,0,0,0,0,1,0,0,0,0,0,0,2,
    2,0,0,0,0,0,0,1,0,1,0,2,2,2,2,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
    2,0,0,0,0,0,0,0,0,2,0,0,0,0,2,
    0,0,0,0,0,0,0,0,0,2,2,0,0,0,2,
    0,0,0,0,0,0,0,0,0,2,2,0,0,0,2,
    2,0,0,0,0,0,0,0,0,2,2,0,2,2,2,
};




Tiles::Tiles()
{
    width = 15;
    hight= 15;

}


int Tiles::getTile(int x, int y)
{
    return map[x + y*hight];
}

void Tiles::displayTiles(QGraphicsScene *scene, QGraphicsView *view)
{
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < hight; ++j) {
            std::cout << "tile : " <<  getTile(i,j) << "\n";
            QColor r;
            if(getTile(i,j) == 0) continue;

            if(getTile(i,j) == 1)
                r = Qt::red;
            else if(getTile(i,j) == 2)
                r = Qt::blue;
            Item* tempRect = new Item;
            tempRect->setPos(view->mapToScene(i*100, j*100));
            tempRect->setColour(r);
            scene->addItem(tempRect);
        }
    }
}
