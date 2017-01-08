#ifndef PROJECTSETTINGS_H
#define PROJECTSETTINGS_H

#include <QString>


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
    QString units_;
    double radius_;
    double units_scale_;
};

#endif // PROJECTSETTINGS_H
