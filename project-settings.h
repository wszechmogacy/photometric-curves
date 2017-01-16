#ifndef PROJECTSETTINGS_H
#define PROJECTSETTINGS_H

#include <QString>


typedef struct {
    QString name;
    unsigned index;
} units_t;

typedef struct {
    unsigned value;
    unsigned index;
} step_t;


class ProjectSettings
{
public:
    ProjectSettings();
    QString student_name_;
    QString class_date_;
    QString student_group_;
    QString source_name_;
    double radius_;
    double units_scale_;
    bool initial_config;
    units_t units;
    step_t step_in_parallel_dir;
    step_t step_in_meridian_dir;
};

#endif // PROJECTSETTINGS_H
