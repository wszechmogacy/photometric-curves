#include <algorithm>
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
    const int slices = 18;
    std::vector<double> parallels(slices);
    std::iota(parallels.begin(), parallels.end(), 0);

    std::transform(parallels.begin(),
                   parallels.end(),
                   parallels.begin(),
                   [](double val) { return (90.0 - (90.0 / slices) * val);}

    );


    qDebug() << "===========================" ;
    for (auto arg : parallels) qDebug() << QString::number(arg);

    double area = 0.0;
    for (double upper_lattidtude : parallels) {
        double lower_lattidtude = upper_lattidtude - 90.0 / slices;

        const double upper_circumference = 2 * ConstNumbers::pi * this->sphere_radius * std::cos(upper_lattidtude * 2 * ConstNumbers::pi / 360.0);
        const double lower_circumference = 2 * ConstNumbers::pi * this->sphere_radius * std::cos(lower_lattidtude * 2 * ConstNumbers::pi / 360.0);
        area += (upper_circumference + lower_circumference) / 2 * calculate_meridian_chunck_length(slices);
    }
    qDebug() << "area=" << QString::number(area);

    //qDebug() << "circ=" << QString::number(upper_circumference) << QString::number(lower_circumference);



    /*
    std::vector<Point> top_layer;
    for (auto arg : data) {
        if (arg.lat_angle_deg == upper_lattidtude) top_layer.push_back(arg);
    }



    for (auto arg : top_layer)
        qDebug() << arg.lat_angle_deg << " " << arg.lon_angle_deg;

*/

    return area;
}
