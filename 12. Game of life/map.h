#ifndef MAP_H
#define MAP_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include <vector>
#include "cell.h"
#include <array>

//static const int Width = 39; /*38; // 36*/
//static const int Height = 9; /*20; //9*/
static const int Width = 150; /*38; // 36*/
static const int Height =100; /*20; //9*/

static const int CellSize = 4;
static char matrix[Width*Height];
static char nextGenMatrix[Width*Height];
static std::array<Cell*, Width*Height> a_cells;


class Map
{
public:
    Map(QGraphicsScene *scene, QGraphicsView *view);
    ~Map();
    void activateCell(int x, int y);
    void checkNeighbours();

private:
    void initialiseRandomMatrix();
    void initialiseMatrixFromBMP();
    char &getCell(int x, int y);
    void addCell(int x, int y, char t);
    Cell* getCellItem(int x, int y);
private:

    QColor red;
    QColor black;
    QGraphicsScene *m_scene = nullptr;
    QGraphicsView *m_view = nullptr;
};

#endif // MAP_H
