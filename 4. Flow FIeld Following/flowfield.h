#ifndef FLOWFIELD_H
#define FLOWFIELD_H
#include <QVector2D>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <vector>
#include "arrow.h"

extern const int Height;
extern const int Width;
extern const size_t matrixSize;
extern const  int resolution;
extern Arrow* matrix[];

class FlowField/*: public QGraphicsItem*/
{
public:
    FlowField(QGraphicsView *view, QGraphicsScene* scene);
    ~FlowField();

    void setField(Arrow* v, int x, int y);
    Arrow* getField(int x, int y);

private:
    void makeArrows();
private:
    QRectF rect;
    QGraphicsView* m_view;
    QGraphicsScene* m_scene;
    int cols, rows;
    std::vector<Arrow*> v_arrowContainer;

};

#endif // FLOWFIELD_H
