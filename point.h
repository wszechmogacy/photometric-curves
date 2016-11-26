#ifndef POINT_H
#define POINT_H

namespace ConstNumbers {
    constexpr double pi = std::acos(-1);
}

class Point {

public:
    double xy_angle_deg;
    double zx_angle_deg;
    double radial;
    double xy_angle_rad;
    double zx_angle_rad;
    double x;
    double y;
    double z;

public:
    Point(double xy_angle_deg, double zx_angle_deg, double radial);
    Point();
    bool operator<(const Point &o) const;
};

#endif /*POINT_H*/
