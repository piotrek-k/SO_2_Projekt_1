#ifndef SO2_PROJEKT_TABLE
#define SO2_PROJEKT_TABLE

#include <tuple>
#include <vector>
#include "RefPoint.h"

class Table {
private:
    int positionX = 0;
    int positionY = 0;
    int numberOfElements = 0;
    std::vector<RefPoint*> refPoints;
    int radius = 10;
    float scaleX = 1;
    float scaleY = 1;
public:
    Table(int posX, int posY, int radius, float scaleX, float scaleY);
    std::tuple<int, int> GetPosition();
    void AddElement(RefPoint* refPoint);
    void RecalculateRefPoints();
};

#endif //SO2_PROJEKT_TABLE