#include "RefPoint.h"

RefPoint::RefPoint(int posX, int posY){
    this->positionX = posX;
    this->positionY = posY;
}

std::tuple<int, int> RefPoint::getPosition()
{
    return std::make_tuple(positionX, positionY);
}