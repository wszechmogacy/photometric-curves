#include <QWidget>

#include <introduction-dialog-window.h>
#include <project-settings.h>
#include <setup-project-dialog-window.h>
#include <ui_introduction-dialog-window.h>

IntroductionDialogWindow::IntroductionDialogWindow(ProjectSettings *proj_settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IntroductionDialogWindow),
    project_settings(proj_settings)
{
    ui->setupUi(this);
}

IntroductionDialogWindow::~IntroductionDialogWindow()
{
    delete ui;
}

void IntroductionDialogWindow::on_createProjectButton_clicked()
{
    SetupProjectDialogWindow window(project_settings);
    window.exec();
    close();
}
