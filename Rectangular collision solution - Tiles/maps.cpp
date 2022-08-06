#include "maps.h"
#include <QDebug>
#include <QRgb>
#include "item.h"

Maps::Maps(QObject *parent) : QObject(parent)
{
    if(!mImage.load(":/map.bmp"))
        qDebug() << "Map was not loaded";

    //    QColor c1 = mImage.pixel(1,1);
    //    QColor c2 = mImage.pixel(2,2);
    //    QColor c3 = mImage.pixel(3,3);

    //    qDebug() << c1.red() << " " << c1.green() << " " << c1.blue();
    //    qDebug() << c2.red() << " " << c2.green() << " " << c2.blue();
    //    qDebug() << c3.red() << " " << c3.green() << " " << c3.blue();
}

QColor Maps::getTile(int x, int y)
{
    return mImage.pixel(x, y );
}

void Maps::displayTiles(QGraphicsScene *scene, QGraphicsView *view)
{
    for (int i = 0; i < mImage.width(); ++i) {
        for (int j = 0; j < mImage.height(); ++j) {
                if(getTile(i,j) == QColor(237, 28,36)) continue;
                QColor r;
                if(getTile(i,j) ==  QColor(0, 0,0)){
                    r = Qt::red;
                    itemCounter++;
                }
                else continue;

                Item* tempRect = new Item;
                tempRect->setPos(view->mapToScene(i*80, j*80));
                tempRect->setColour(r);


                scene->addItem(tempRect);
            }
        }

    qDebug() << "items: " << itemCounter  ;
}
