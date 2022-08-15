#ifndef MAPLOADER_H
#define MAPLOADER_H
#include <QImage>
#include <vector>

class MapLoader
{
public:
    MapLoader();
    std::vector<int>& loadMap();

private:
    QImage mImage;
    std::vector<int> v;

};

#endif // MAPLOADER_H
