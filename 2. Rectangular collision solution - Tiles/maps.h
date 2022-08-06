#ifndef MAPS_H
#define MAPS_H
#include <QObject>
#include <QImage>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <vector>
//extern QPixelFormat map[];

class Maps : public QObject
{
    Q_OBJECT
public:
    explicit Maps(QObject *parent = nullptr);
    QColor getTile(int x, int y);
    void displayTiles(QGraphicsScene *scene, QGraphicsView *view);
signals:
private:
    QImage mImage;
    int itemCounter =0;
};

#endif // MAPS_H
