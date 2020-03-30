#ifndef POINT
#define POINT

#include <iostream>
#include <cmath>

class Point final
{
    friend std::ostream& operator<<(std::ostream&, const Point&);
    friend std::istream& operator>>(std::istream&, Point&);
private:
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

public:
    Point() = default;
    Point(const double &x_, const double &y_, const double &z_) : 
		x(x_), y(y_), z(z_) { }
    Point(const Point&);
    
	double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }
    
    void rotateZ(const double &phi);
    
    ~Point() noexcept = default;
};
#endif

