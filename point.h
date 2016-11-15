#ifndef __POINT_H__
#define __POINT_H__

class Point {
    public:
    Point(double xy_angle_deg, double zx_angle_deg, double radial);
    Point();
    double xy_angle_deg();
    double zx_angle_deg()
    double radial();
    double xy_angle_rad();
    double zx_angle_rad();
    double x();
    double y();
    double z();
    private:
    double xy_angle_deg;
    double zx_angle_deg;
    double radial;
    double xy_angle_rad;
    double zx_angle_rad;
    double x;
    double y;
    double z;
};

#endif /* __POINT_H__ */
