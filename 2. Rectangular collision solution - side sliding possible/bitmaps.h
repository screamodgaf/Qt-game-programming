#ifndef BITMAPS_H
#define BITMAPS_H
#include <QObject>
#include <QImage>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <vector>
//extern QPixelFormat map[];

class Bitmaps : public QObject
{
    Q_OBJECT
public:
    explicit Bitmaps(QObject *parent = nullptr);

    QColor getTile(int x, int y);
    void displayTiles(QGraphicsScene *scene, QGraphicsView *view);


signals:
private:
//    std::vector<QColor> map;
    QImage mImage;
    int itemCounter =0;
};

#endif // BITMAPS_H
