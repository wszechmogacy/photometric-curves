#ifndef INTRODUCTIONDIALOGWINDOW_H
#define INTRODUCTIONDIALOGWINDOW_H

#include <QDialog>

#include <project-settings.h>

namespace Ui {
class IntroductionDialogWindow;
}

class IntroductionDialogWindow : public QDialog
{
    Q_OBJECT

public:
    explicit IntroductionDialogWindow(ProjectSettings *proj_settings, QWidget *parent = 0);
    ~IntroductionDialogWindow();

private slots:
    void on_createProjectButton_clicked();

private:
    Ui::IntroductionDialogWindow *ui_;
    ProjectSettings *project_settings_;
};

#endif // INTRODUCTIONDIALOGWINDOW_H
