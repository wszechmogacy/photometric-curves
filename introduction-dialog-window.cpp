#include <QWidget>

#include <introduction-dialog-window.h>
#include <project-settings.h>
#include <setup-project-dialog-window.h>
#include <ui_introduction-dialog-window.h>

IntroductionDialogWindow::IntroductionDialogWindow(ProjectSettings *proj_settings, QWidget *parent) :
    QDialog(parent),
    ui_(new Ui::IntroductionDialogWindow),
    project_settings_(proj_settings)
{
    ui_->setupUi(this);
    ui_->createProjectButton->setText(tr("Create Project"));
    ui_->openProjectButton->setText(tr("Open Project"));
}

IntroductionDialogWindow::~IntroductionDialogWindow()
{
    delete ui_;
}

void IntroductionDialogWindow::on_createProjectButton_clicked()
{
    SetupProjectDialogWindow window(project_settings_);
    window.exec();
    close();
}
