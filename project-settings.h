#ifndef PROJECTSETTINGS_H
#define PROJECTSETTINGS_H

#include <QString>


typedef struct {
    QString name;
    unsigned index;
} units_t;


class ProjectSettings
{
public:
    ProjectSettings();
    QString student_name_;
    QString class_date_;
    QString student_group_;
    QString source_name_;
    unsigned step_in_parallel_dir_;
    unsigned step_in_meridian_dir_;
    double radius_;
    double units_scale_;
    bool initial_config;
    units_t units;
};

#endif // PROJECTSETTINGS_H
