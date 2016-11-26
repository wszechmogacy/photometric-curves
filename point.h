#ifndef POINT_H
#define POINT_H

#include <cmath>

namespace ConstNumbers {
    constexpr double pi = std::acos(-1);
}

class Point {

public:
    double lon_angle_deg;
    double lat_angle_deg;
    double radial;
    double lon_angle_rad;
    double lat_angle_rad;
    double x;
    double y;
    double z;

public:
    Point(double lon_angle_deg, double lat_angle_deg, double radial);
    Point();
    bool operator<(const Point &o) const;
};

#endif /*POINT_H*/
