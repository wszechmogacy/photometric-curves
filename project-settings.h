#ifndef PROJECTSETTINGS_H
#define PROJECTSETTINGS_H

#include <QString>


class ProjectSettings
{
public:
    ProjectSettings();
    QString student_name;
    QString class_date;
    QString student_group;
    QString source_name;
    unsigned step_in_parallel;
    unsigned step_in_meridian;
    QString units;
    unsigned radius;
};

#endif // PROJECTSETTINGS_H
