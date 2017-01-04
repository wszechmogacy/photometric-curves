#include <cmath>
#include <QDebug>

#include <point.h>


Point::Point() :
    lon_angle_deg(0), lat_angle_deg(0), radial(0),
    lon_angle_rad(0),
    lat_angle_rad(0),
    x(0), y(0), z(0)
{

}


Point::Point(double lon_angle_deg, double lat_angle_deg, double radial) :
    lon_angle_deg(lon_angle_deg), lat_angle_deg(lat_angle_deg), radial(radial),
    lon_angle_rad(lon_angle_deg * 2 * ConstNumbers::pi / 360),
    lat_angle_rad(lat_angle_deg * 2 * ConstNumbers::pi / 360),
    x(radial * sin(lat_angle_rad) * cos(lon_angle_rad)),
    y(radial * sin(lat_angle_rad) * sin(lon_angle_rad)),
    z(radial * cos(lat_angle_rad))
{
}

bool Point::operator<(const Point &o) const {
         if (lon_angle_deg != o.lon_angle_deg) {
             return lon_angle_deg < o.lon_angle_deg;
         }
         if (lat_angle_deg != o.lat_angle_deg) {
             return lat_angle_deg < o.lat_angle_deg;
         }
         return radial < o.radial;
}
