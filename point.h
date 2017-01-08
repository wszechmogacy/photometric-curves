#ifndef POINT_H
#define POINT_H

#include <cmath>

namespace ConstNumbers {
const double pi = std::acos(-1);
}

class Point {

public:
    double lon_angle_deg_;
    double lat_angle_deg_;
    double radial_;
    double lon_angle_rad_;
    double lat_angle_rad_;
    double x_;
    double y_;
    double z_;

public:
    Point(double lon_angle_deg_, double lat_angle_deg_, double radial_);
    Point();
    bool operator<(const Point &o) const;
};

#endif /*POINT_H*/
