#ifndef SETUPPROJECTDIALOGWINDOW_H
#define SETUPPROJECTDIALOGWINDOW_H

#include <QDialog>
#include "project-settings.h"

namespace Ui {
class SetupProjectDialogWindow;
}

class SetupProjectDialogWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SetupProjectDialogWindow(ProjectSettings *proj, QWidget *parent = 0);
    ~SetupProjectDialogWindow();

private slots:
    void on_startProjectButton_clicked();

private:
    Ui::SetupProjectDialogWindow *ui;
    ProjectSettings *project_settings;
};

#endif // SETUPPROJECTDIALOGWINDOW_H
