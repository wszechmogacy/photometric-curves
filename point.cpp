#include <cmath>
#include "Point.h"


const double pi = std::acos(-1);



Point::Point() :
    xy_angle_deg(0), zx_angle_deg(0), radial(0),
    xy_angle_rad(0),
    zx_angle_rad(0),
    x(0), y(0), z(0)
{
}


Point::Point(double xy_angle_deg, double zx_angle_deg, double radial) :
    xy_angle_deg(xy_angle_deg), zx_angle_deg(zx_angle_deg), radial(radial),
    xy_angle_rad(xy_angle_deg * 2 * pi / 360),
    zx_angle_rad(zx_angle_deg * 2 * pi / 360),
    x(radial * cos(zx_angle_rad) * cos(xy_angle_rad)),
    y(radial * cos(zx_angle_rad) * sin(xy_angle_rad)),
    z(radial * sin(zx_angle_rad))
{
    //obslugla bledow. czy wszystkie sie dalo skonwertowac do double/double. Wybrac odpowiedni typ
    //https://pl.wikipedia.org/wiki/Uk%C5%82ad_wsp%C3%B3%C5%82rz%C4%99dNych_sferycznych
    //i czy punkty mieszcza się w zakresie 0<2pi czy jednego pi a promien > 0
    //czy kąty będą intami czy doubleami?
}
double Point::xy_angle_deg();
{
    return xy_angle_deg;
}


double Point::zx_angle_deg()
{
    return zx_angle_deg;
}


double Point::radial();
{
    return radial;
}


double Point::xy_angle_rad();
{
    return xy_angle_rad;
}


double Point::zx_angle_rad();
{
    return zx_angle_rad;
}


double Point::x();
{
    return x;
}


double Point::y();
{
    return y
}


double Point::z();
{
    return z;
}

