#ifndef POINT_H
#define POINT_H

class Point {

public:
    const double xy_angle_deg;
    const double zx_angle_deg;
    const double radial;
    const double xy_angle_rad;
    const double zx_angle_rad;
    const double x;
    const double y;
    const double z;

public:
    Point(double xy_angle_deg, double zx_angle_deg, double radial);
    Point();
};

#endif /*POINT_H*/
