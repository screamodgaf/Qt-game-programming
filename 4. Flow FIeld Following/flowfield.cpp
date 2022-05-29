#include "flowfield.h"
#include <QDebug>
#include <termcolor.hpp>
FlowField::FlowField(QGraphicsView* view, QGraphicsScene* scene): m_view{view},
    m_scene{scene}
{
    qDebug() << "FlowField()";

//    cols = m_view->width()/resolution;
//    rows = m_view->height()/resolution;

    makeArrows();

}

void FlowField::makeArrows()
{
//    std::cout << cols << rows << "\n";
    for(int i = 0; i < Width/resolution; i ++){
        for(int j = 0; j < Height/resolution; j ++){
            Arrow* a = new Arrow;
            a->setPos(i*resolution , j*resolution); ///pos on the screen/scene
            int rDegrees = std::rand()%180; /// is horizontal lines, 90* is vertical lines | 360 means posibility opposite vectors
            a->setRotation(rDegrees);
//            std::cout << termcolor::red << "rDegrees: " << rDegrees << termcolor::reset<< "\n";
//            qDebug() << "a address at " << i*resolution << " " << j*resolution << " : " << a;
            setField(a, i, j); ///puts arrow into Arrow matrix
            v_arrowContainer.push_back(a);
            m_scene->addItem(a);
        }
    }
}

void FlowField::setField(Arrow *v, int x, int y) ///puts arrow into Arrow matrix
{
    matrix[x  + y  * Height/resolution ] = v;
}

Arrow* FlowField::getField(int x, int y)
{
    int index = x/resolution+ y/resolution * Height/resolution;
//    qDebug() << "index " << index <<   " matrixSize: " << matrixSize;
    if(index < matrixSize) return matrix[index];
    else return nullptr;
}

