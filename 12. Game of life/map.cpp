#include "map.h"
#include <iostream>
#include <random>
#include "maploader.h"
/*
 * cells on map shouldnt be sent on the borders
 */

Map::Map(QGraphicsScene *scene, QGraphicsView *view): m_scene{scene}, m_view{view}
{
    red = Qt::white;
    black = Qt::black;

        initialiseMatrixFromBMP();


//    initialiseRandomMatrix();

}

void Map::initialiseRandomMatrix()
{
    for (int y = 1; y < Height-1; ++y) { ///so not to draw on the border, as if(x==0 || y==0 || x == Width-1 || y == Height-1) in Map::checkNeighbours() prevents checking on the borders, so there would be a "frame artefact"
        for (int x = 1; x < Width-1; ++x) {
            int t =  std::rand()%2; /// 0,1
            matrix[x+ y*Width] = t;
            addCell(x,y, t);
        }
    }
}

void Map::initialiseMatrixFromBMP()
{
    MapLoader l;
    std::vector<int> v = l.loadMap();

    for (int y = 0; y < Height; ++y) {
        for (int x = 0; x < Width; ++x) { //jiggering of the solid elements is caused by flag n and this +vel prevents it
            matrix[x+ y*Width] = v[x+ y*Width];
            addCell(x,y, matrix[x+ y*Width]);
        }
    }
}

void Map::checkNeighbours()
{
    for (int y = 0; y < Height; ++y) {
        for (int x = 0; x < Width; ++x) {
            int sumOfNeighbours = 0;
            if(x==0 || y==0 || x == Width-1 || y == Height-1)
                continue;
            sumOfNeighbours += getCell(x-1, y-1); //upper left corner
            sumOfNeighbours += getCell(x+1, y-1); //upper right corner
            sumOfNeighbours += getCell(x-1, y+1); //lower left corner
            sumOfNeighbours += getCell(x+1, y+1); //lower right corner

            sumOfNeighbours += getCell(x, y-1); //up
            sumOfNeighbours += getCell(x, y+1); //down
            sumOfNeighbours += getCell(x-1, y); //left
            sumOfNeighbours += getCell(x+1, y); //right

            if(getCell(x,y) == 0 && sumOfNeighbours == 3){
                nextGenMatrix[x+ y*Width] =1;
                getCellItem(x,y)->setColor(red);
            }else if(getCell(x,y) == 1 && (sumOfNeighbours<2 || sumOfNeighbours >3)){
                nextGenMatrix[x+ y*Width] =0;
                getCellItem(x,y)->setColor(black);
            }else ///preserve previous state:
                nextGenMatrix[x+ y*Width] = getCell(x,y);
        }
    }

    ///matrix = nextGenMatrix;
    std::copy(std::begin(nextGenMatrix), std::end(nextGenMatrix), std::begin(matrix));

}



char& Map::getCell(int x, int y)
{
    return matrix[x+ y*Width];
}

Cell* Map::getCellItem(int x, int y)
{
    return a_cells[x+ y*Width];
}



void Map::addCell(int x, int y, char t)
{
    Cell* cell = new Cell(CellSize);
    cell->setPos(m_view->mapToScene(x*CellSize, y*CellSize));
    QColor red = Qt::red;
    QColor black = Qt::black;
    if(t)
        cell->setColor(red);
    else
        cell->setColor(black);
    m_scene->addItem(cell);
    a_cells[x+ y*Width] = cell;
}

void Map::activateCell(int x, int y)
{
    matrix[x+ y*Width] =1;
    QColor red = Qt::red;
    getCellItem(x,y)->setColor(red);
}

Map::~Map()
{
    for (int i = 0; i < a_cells.size(); ++i) {
        delete a_cells[i];
        a_cells[i] = nullptr;
    }
}



