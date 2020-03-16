#include "RefPoint.h"

RefPoint::RefPoint(int posX, int posY)
{
    this->positionX = posX;
    this->positionY = posY;
}

std::tuple<int, int> RefPoint::getPosition()
{
    return std::make_tuple(positionX, positionY);
}

void RefPoint::SetPosition(std::tuple<int, int> newPos)
{
    this->positionX = std::get<0>(newPos);
    this->positionY = std::get<1>(newPos);
}

void RefPoint::SetPosition(int posX, int posY)
{
    this->positionX = posX;
    this->positionY = posY;
}