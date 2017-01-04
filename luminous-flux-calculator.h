#ifndef LUMINOUSFLUXCALCULATOR_H
#define LUMINOUSFLUXCALCULATOR_H

#include <vector>

#include <point.h>

class LuminousFluxCalculator
{
public:
    explicit LuminousFluxCalculator(double radius);
    double operator() (std::vector<Point> &data, int meridian_points_count);

private:
    const double sphere_radius;
    double calculate_meridian_chunck_length(int meridian_points_count);
    double average_value_on_parallel(double lattitude, std::vector<Point> &data);
    std::vector<double> create_paralles_list(int meridian_points_count);
};

#endif // LUMINOUSFLUXCALCULATOR_H
