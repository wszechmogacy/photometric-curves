#include <cmath>
#include <QDebug>
#include "point.h"




Point::Point() :
    lon_angle_deg(0), zx_angle_deg(0), radial(0),
    lon_angle_rad(0),
    zx_angle_rad(0),
    x(0), y(0), z(0)
{

}


Point::Point(double lon_angle_deg, double zx_angle_deg, double radial) :
    lon_angle_deg(lon_angle_deg), zx_angle_deg(zx_angle_deg), radial(radial),
    lon_angle_rad(lon_angle_deg * 2 * ConstNumbers::pi / 360),
    zx_angle_rad(zx_angle_deg * 2 * ConstNumbers::pi / 360),
    x(radial * cos(zx_angle_rad) * cos(lon_angle_rad)),
    y(radial * cos(zx_angle_rad) * sin(lon_angle_rad)),
    z(radial * sin(zx_angle_rad))
{
    //obslugla bledow. czy wszystkie sie dalo skonwertowac do double/double. Wybrac odpowiedni typ
    //https://pl.wikipedia.org/wiki/Uk%C5%82ad_wsp%C3%B3%C5%82rz%C4%99dNych_sferycznych
    //i czy punkty mieszcza się w zakresie 0<2pi czy jednego pi a promien > 0
    //czy kąty będą intami czy doubleami?
   // qDebug() << "xy=" << QString::number(lon_angle_deg) << " zx=" << QString::number(zx_angle_deg) << " radial=" << QString::number(radial) << endl;
   // qDebug() << "x=" << QString::number(x) << " y=" << QString::number(y) << " z=" << QString::number(z) << endl;
}

bool Point::operator<(const Point &o) const {
         if (x != o.x) {
             return x < o.x;
         }
         if (y != o.y) {
             return y < o.y;
         }
         return z < o.z;
}
