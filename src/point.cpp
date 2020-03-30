#include "point.h"

Point::Point(const Point &point)
{
    if (&point != this)
    {
        x = point.x;
        y = point.y;
        z = point.z;
    }
}

void Point::rotateZ(const double &phi)
{
    double x_ = x;
    x = x_ * cos(phi) + y * sin(phi);
    y = -x_ * sin(phi) + y * cos(phi);
}

std::ostream& operator<<(std::ostream &out, const Point &point)
{	
    return out << point.x << " " << point.y << " " << point.z;
}
std::istream& operator>>(std::istream &in, Point &point)
{	
    return in >> point.x >> point.y >> point.z;
}
