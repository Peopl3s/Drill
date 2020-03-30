#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <memory>

#include "point.h"
#include "position.h"

class Utils final
{
public:
    Utils(const Utils&) = delete;
    Utils& operator=(const Utils&) = delete;

    static Utils& getInstance();
    void calculate(const std::string&);

    const std::string getTempfile() const;
    double getWidth() const { return width; }
    double getHeight() const { return height; }

private:
    Utils(){}
    static std::unique_ptr<Utils> instance;
    double width{0.0}, height{0.0};
    const std::string tempFile{"decart.txt"};
    Point calcNewPoint(const Position&, const Position&, const Point&);
    void minMaxValueOfXZ(double&, double&, double&, const double &, const double &);
};

#endif
