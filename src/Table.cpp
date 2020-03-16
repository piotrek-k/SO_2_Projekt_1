#include "Table.h"
#define PI 3.14159265
#include <math.h> /* sin */

Table::Table(int posX, int posY, int radius)
{
    this->positionX = posX;
    this->positionY = posY;
    this->radius = radius;
}

std::tuple<int, int> Table::GetPosition()
{
    return std::make_tuple(positionX, positionY);
}

void Table::AddElement(RefPoint *refPoint)
{
    this->refPoints.push_back(refPoint);
    this->RecalculateRefPoints();
}

void Table::RecalculateRefPoints()
{
    for (int x = 0; x < refPoints.size(); x++)
    {
        float degrees = x * (360 / (float)refPoints.size());
        float radians = degrees * PI / 180;
        int newPosX = sin(radians) * this->radius + this->positionX;
        int newPosY = cos(radians) * this->radius + this->positionY;

        refPoints[x]->SetPosition(newPosX, newPosY);
    }
}