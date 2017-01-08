#include <cmath>
#include <QDebug>

#include <point.h>


Point::Point() :
    lon_angle_deg_(0), lat_angle_deg_(0), radial_(0),
    lon_angle_rad_(0),
    lat_angle_rad_(0),
    x_(0), y_(0), z_(0)
{

}


Point::Point(double lon_angle_deg, double lat_angle_deg, double radial) :
    lon_angle_deg_(lon_angle_deg), lat_angle_deg_(lat_angle_deg), radial_(radial),
    lon_angle_rad_(lon_angle_deg * 2 * ConstNumbers::pi / 360),
    lat_angle_rad_(lat_angle_deg * 2 * ConstNumbers::pi / 360),
    x_(radial * sin(lat_angle_rad_) * cos(lon_angle_rad_)),
    y_(radial * sin(lat_angle_rad_) * sin(lon_angle_rad_)),
    z_(radial * cos(lat_angle_rad_))
{
}

bool Point::operator<(const Point &o) const {
         if (lon_angle_deg_ != o.lon_angle_deg_) {
             return lon_angle_deg_ < o.lon_angle_deg_;
         }
         if (lat_angle_deg_ != o.lat_angle_deg_) {
             return lat_angle_deg_ < o.lat_angle_deg_;
         }
         return radial_ < o.radial_;
}
