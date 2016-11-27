#include <algorithm>
#include <numeric>
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
    auto parallels = create_paralles_list(meridian_points_count);

    double area = 0.0;
    double flux = 0.0;
    for (double upper_lattidtude : parallels) {
        double lower_lattidtude = upper_lattidtude - 90.0 / meridian_points_count;

        const double upper_circumference = 2 * ConstNumbers::pi * this->sphere_radius * std::cos(upper_lattidtude * 2 * ConstNumbers::pi / 360.0);
        const double lower_circumference = 2 * ConstNumbers::pi * this->sphere_radius * std::cos(lower_lattidtude * 2 * ConstNumbers::pi / 360.0);
        area = (upper_circumference + lower_circumference) / 2 * calculate_meridian_chunck_length(meridian_points_count);

        for (auto arg : parallels) qDebug() << QString::number(arg);

        double upper_sum = sum_parallels_values(upper_lattidtude, data);
        double lower_sum = sum_parallels_values(lower_lattidtude, data);

        flux += (upper_sum + lower_sum) * area / 2;
    }

    return flux;
}

double LuminousFluxCalculator::sum_parallels_values(double lattidtude, std::vector<Point> &data)
{
    std::vector<Point> points_on_layer;
    for (auto arg : data) {
        if (arg.lat_angle_deg == lattidtude) points_on_layer.push_back(arg);
    }
    double sum = std::accumulate(points_on_layer.begin(), points_on_layer.end(), 0.0,
                                 [](double val, const Point &point){ return val + point.radial;}
    );
    qDebug() << "sum=" << QString::number(sum) << " for lat=" << QString::number(lattidtude);
    return sum;
}

std::vector<double> LuminousFluxCalculator::create_paralles_list(int meridian_points_count)
{
    const int slices = meridian_points_count;
    std::vector<double> parallels(slices);
    std::iota(parallels.begin(), parallels.end(), 0.0);

    std::transform(parallels.begin(),
                   parallels.end(),
                   parallels.begin(),
                   [&slices](double val) { return (90.0 - (90.0 / slices) * val);}
    );
    return parallels;
}
