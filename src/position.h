#ifndef POSITION
#define POSITION

#include <iostream>

class Position final
{
    friend std::ostream& operator<<(std::ostream&, const Position&);
	
private:
    double depth = 0.0;
    double azimuth = 0.0;
    double inclination = 0.0;

public:
    Position() = default;
    Position(const double &depth_, const double &azimuth_, const double &inclination_):
        depth(depth_), azimuth(azimuth_), inclination(inclination_) { }
    Position(const Position&);

	double getDepth() const { return depth; }
    double getAzimuth() const { return azimuth; }
    double getInclination() const { return inclination; }

    ~Position() noexcept = default;
};
#endif
