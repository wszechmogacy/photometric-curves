#include "setup-project-dialog-window.h"
#include "ui_setup-project-dialog-window.h"
#include "project-settings.h"

SetupProjectDialogWindow::SetupProjectDialogWindow(ProjectSettings *proj, QWidget *parent) :
    QDialog(parent),
    project_settings(proj),
    ui(new Ui::SetupProjectDialogWindow)
{
    ui->setupUi(this);

    const QStringList unitsItems = {"uW/cm^2", "W/m^2", "lm/m^2"};
    ui->unitsComboBox->addItems(unitsItems);

    const QStringList stepParalleItems = {"5", "10", "15"};
    ui->stepParallelComboBox->addItems(stepParalleItems);
    ui->stepInMeridianComboBox->addItems(stepParalleItems);
}

SetupProjectDialogWindow::~SetupProjectDialogWindow()
{
    delete ui;
}

void SetupProjectDialogWindow::on_startProjectButton_clicked()
{
    project_settings->student_name = ui->studentNameField->text();
    project_settings->class_date = ui->classesDateField->text();
    project_settings->student_group = ui->studentGroupField->text();
    project_settings->source_name = ui->lightSourceField->text();
    project_settings->step_in_parallel = ui->stepParallelComboBox->currentText().toUInt();
    project_settings->step_in_meridian = ui->stepInMeridianComboBox->currentText().toUInt();
    project_settings->units = ui->unitsComboBox->currentText();
    project_settings->radius = ui->radiusField->text().toUInt();
    close();
}
