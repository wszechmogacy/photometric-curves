#include <QDebug>
#include <vector>

#include "luminous-flux-calculator.h"

LuminousFluxCalculator::LuminousFluxCalculator(double radius) :
    sphere_radius(radius)
{

}

double LuminousFluxCalculator::calculate_meridian_chunck_length(int meridian_points_count)
{
    const double half_meridian_length = 0.5 * ConstNumbers::pi * this->sphere_radius;
    return half_meridian_length / meridian_points_count;
}

double LuminousFluxCalculator::operator() (std::vector<Point> &data, int meridian_points_count, int parallel_points_count)
{
    for (auto arg : data)
        qDebug() << arg.lon_angle_deg << " " << arg.lat_angle_deg;

    auto it = std::find_if(
                data.begin(),
                data.end(),
                [](const Point &arg){ return (arg.lon_angle_deg == 0.0 && arg.lat_angle_deg == 90.0); }
    );
    if (it != data.end()) {
        qDebug() << "value found: " << (*it).lon_angle_deg << " " <<  (*it).lat_angle_deg << " " << (*it).radial;
    } else {
        //wyjatek
    }


    return 0.0;
}
