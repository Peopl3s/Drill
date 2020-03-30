#include "utils.h"

#include <cmath>
#include <fstream>
#include <stdexcept>

#include "json.hpp"

using json = nlohmann::json;

std::unique_ptr<Utils> Utils::instance = nullptr;

Utils& Utils::getInstance()
{
    if(instance == nullptr)
        instance = std::unique_ptr<Utils>(new Utils());
    return *instance;
}

const std::string Utils::getTempfile() const
{
    return tempFile;
}

Point Utils::calcNewPoint(const Position &leftPoint, const Position &rightPoint, const Point &previousPoint)
{
    double d = acos(sin(leftPoint.getInclination()) * sin(rightPoint.getInclination()) *
                    cos(leftPoint.getAzimuth()- rightPoint.getAzimuth()) +
                    cos(leftPoint.getInclination()) * cos(rightPoint.getInclination()));
    double t;
    if(d != 0)
        t = ((rightPoint.getDepth() - leftPoint.getDepth()) * tan(d / 2)) / d;
    else
        t = ((rightPoint.getDepth() - leftPoint.getDepth())) / 2;

    double dz = t * (cos(leftPoint.getInclination()) + cos(rightPoint.getInclination()));
    double dy = t * (sin(leftPoint.getInclination()) * sin(leftPoint.getAzimuth()) +
                     sin(rightPoint.getInclination()) * sin(rightPoint.getAzimuth()));
    double dx = t * (sin(leftPoint.getInclination()) * cos(leftPoint.getAzimuth()) +
                     sin(rightPoint.getInclination()) * cos(rightPoint.getAzimuth()));

    return Point(previousPoint.getX() + dx, previousPoint.getY() + dy, previousPoint.getZ() + dz);
}

void Utils::calculate(const std::string &inputJsonFile)
{
    std::ifstream inputFile{inputJsonFile};
    json jsonObject;
    if (inputFile.is_open())
    {
        inputFile >> jsonObject;
        inputFile.close();
    } 
	else
    {
        throw std::runtime_error("Ошибка открытия файла");
    }
	
    std::ofstream tempOutputFile{Utils::tempFile};
	
    Point point{};
    tempOutputFile << point;
    
    double minX = point.getX(), maxX = point.getX(), maxZ = point.getZ();
    
    Position lhs, rhs;	
    if(jsonObject[0].at("depth") != 0)
    {
    	try
		{
	    	lhs = Position();
            rhs = Position(static_cast<double>(jsonObject[0].at("depth")),
                           static_cast<double>(jsonObject[0].at("azimuth")),
                           static_cast<double>(jsonObject[0].at("inclination")));
	    	point = calcNewPoint(lhs, rhs, point);
    	} 
        catch(const json::exception &jsonParseException)
		{
             throw jsonParseException;
        }
        
        minMaxValueOfXZ(minX, maxX, maxZ, point.getX(), point.getZ());
        
        tempOutputFile << "\n" << point;
	}
			
    for (int i = 0; i != static_cast<int>(jsonObject.size()) - 1; ++i)
    {
    	try
		{
            lhs = Position(static_cast<double>(jsonObject[i].at("depth")),
                           static_cast<double>(jsonObject[i].at("azimuth")),
                           static_cast<double>(jsonObject[i].at("inclination")));

            rhs = Position(static_cast<double>(jsonObject[i+1].at("depth")),
                           static_cast<double>(jsonObject[i+1].at("azimuth")),
                           static_cast<double>(jsonObject[i+1].at("inclination")));

	        point = calcNewPoint(lhs, rhs, point); 
        } 
        catch(const json::exception &jsonParseException)
		{
            throw jsonParseException;
        }
        
        minMaxValueOfXZ(minX, maxX, maxZ, point.getX(), point.getZ());
        		
        tempOutputFile << "\n" << point;
    }

    tempOutputFile.close();
    
    height = maxZ;
    width = maxX - minX;
}

void Utils::minMaxValueOfXZ(double &minX, double &maxX, double &maxZ,
                            const double &valueX, const double &valueZ)
{
    if(minX > valueX)
        minX = valueX;
    else
        if(maxX < valueX)
            maxX = valueX;
    if(maxZ < valueZ)
        maxZ = valueZ;
}


