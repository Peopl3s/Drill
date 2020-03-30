#include "position.h"

Position::Position(const Position &position)
{
    if (&position != this)
    {
        depth = position.depth;
        azimuth = position.azimuth;
        inclination = position.inclination;
    }
}

std::ostream& operator<<(std::ostream &out, const Position &position)
{
    return out << "Depth: " << position.depth << " Azimuth: " << position.azimuth << " Inclination: " << position.inclination;
}
