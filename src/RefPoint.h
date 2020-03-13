#ifndef SO2_PROJEKT_IREFPOINT
#define SO2_PROJEKT_IREFPOINT

#include <tuple>

class RefPoint {
private:
    int positionX = 0;
    int positionY = 0;
public:
    RefPoint(int posX, int posY);
    std::tuple<int, int> getPosition();
};

#endif //SO2_PROJEKT_IREFPOINT