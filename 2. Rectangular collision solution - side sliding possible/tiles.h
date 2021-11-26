#ifndef TILES_H
#define TILES_H
#include <QGraphicsView>
#include <QGraphicsScene>

extern int map[];

class Tiles
{
public:
    Tiles();
    int getTile(int col, int row);
    void displayTiles(QGraphicsScene* scene, QGraphicsView* view);
private:
    int hight;
    int width;

};

#endif // TILES_H
