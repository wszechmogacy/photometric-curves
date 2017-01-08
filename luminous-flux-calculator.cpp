#include <algorithm>
#include <numeric>
#include <QDebug>
#include <vector>

#include <luminous-flux-calculator.h>

LuminousFluxCalculator::LuminousFluxCalculator(double radius) :
    sphere_radius_(radius)
{

}

double LuminousFluxCalculator::calculate_meridian_chunck_length(int meridian_points_count)
{
    const double half_meridian_length = 0.5 * ConstNumbers::pi * this->sphere_radius_;
    return half_meridian_length / meridian_points_count;
}

double LuminousFluxCalculator::operator() (std::vector<Point> &data, double scale, int meridian_points_count)
{

    auto parallels = create_paralles_list(meridian_points_count);

    double area = 0.0;
    double flux = 0.0;
    for (double upper_lattidtude : parallels) {

        double lower_lattidtude = upper_lattidtude + 90.0 / meridian_points_count;

        const double upper_circumference = 2.0 * ConstNumbers::pi * this->sphere_radius_ * std::sin(static_cast<double>(upper_lattidtude) / 360.0 * 2.0 * ConstNumbers::pi);
        const double lower_circumference = 2.0 * ConstNumbers::pi * this->sphere_radius_ * std::sin(static_cast<double>(lower_lattidtude) / 360.0 * 2.0 * ConstNumbers::pi);

        area = (upper_circumference + lower_circumference) / parallels.size() * calculate_meridian_chunck_length(meridian_points_count) / 2;

        const double upper_average = average_value_on_parallel(upper_lattidtude, data) * scale;
        const double lower_average = average_value_on_parallel(lower_lattidtude, data) * scale;

        flux += (upper_average + lower_average) * area;
    }

    qDebug() << "lum: " << QString::number(flux, 'g', 8);
    return flux;
}

double LuminousFluxCalculator::average_value_on_parallel(double lattidtude, std::vector<Point> &data)
{
    std::vector<Point> points_on_layer;
    for (auto arg : data) {
        if (arg.lat_angle_deg_ == lattidtude) points_on_layer.push_back(arg);
    }

    double sum = std::accumulate(points_on_layer.begin(), points_on_layer.end(), 0.0,
                                 [](double val, const Point &point){ return val + point.radial_;}
    );

    return sum / static_cast<double>(points_on_layer.size());
}

std::vector<double> LuminousFluxCalculator::create_paralles_list(int meridian_points_count)
{
    const int slices = meridian_points_count;
    std::vector<double> parallels(slices);
    std::iota(parallels.begin(), parallels.end(), 0.0);

    std::transform(parallels.begin(),
                   parallels.end(),
                   parallels.begin(),
                   [&slices](double val) { return (90.0 / slices) * val;}
    );
    return parallels;
}
