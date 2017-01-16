#ifndef SETUPPROJECTDIALOGWINDOW_H
#define SETUPPROJECTDIALOGWINDOW_H

#include <QDialog>

#include <project-settings.h>

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
    Ui::SetupProjectDialogWindow *ui_;
    ProjectSettings *project_settings_;
    QList< QPair<QString, double>> units_items_;
    void handleOnStartProjectButton_clicked();
    void putInitialValuesToProjectSettingsWindow();
    void putRuntimeValuesToProjectSettingsWindow();
};

#endif // SETUPPROJECTDIALOGWINDOW_H
