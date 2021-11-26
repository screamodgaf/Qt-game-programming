#include "bitmaps.h"
#include <QDebug>
#include <QRgb>
#include "item.h"
Bitmaps::Bitmaps(QObject *parent) : QObject(parent)
{

    //    QImage(":/images/image1.jpg")
    mImage.load("D:/Qt_workspace/graphics1/map.bmp");
    //    QColor c1 = mImage.pixel(1,1);
    //    QColor c2 = mImage.pixel(2,2);
    //    QColor c3 = mImage.pixel(3,3);

    //    qDebug() << c1.red() << " " << c1.green() << " " << c1.blue();
    //    qDebug() << c2.red() << " " << c2.green() << " " << c2.blue();
    //    qDebug() << c3.red() << " " << c3.green() << " " << c3.blue();



}

QColor Bitmaps::getTile(int x, int y)
{
    return mImage.pixel(x, y );
//    return map[x + y*mImage.height()];
}

void Bitmaps::displayTiles(QGraphicsScene *scene, QGraphicsView *view)
{
    for (int i = 0; i < mImage.width(); ++i) {
        for (int j = 0; j < mImage.height(); ++j) {
                if(getTile(i,j) == QColor(237, 28,36)) continue;
                QColor r;
                if(getTile(i,j) ==  QColor(0, 0,0)){
                    r = Qt::red;
                    itemCounter++;
                }else continue;
//                else if(getTile(i,j) == 2)
//                    r = Qt::blue;
                Item* tempRect = new Item;
                tempRect->setPos(view->mapToScene(i*80, j*80));
                tempRect->setColour(r);


                scene->addItem(tempRect);
            }
        }

    qDebug() << "items: " << itemCounter  ;
}
