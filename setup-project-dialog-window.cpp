#include <QWidget>

#include <project-settings.h>
#include <setup-project-dialog-window.h>
#include <ui_setup-project-dialog-window.h>


SetupProjectDialogWindow::SetupProjectDialogWindow(ProjectSettings *proj, QWidget *parent) :
    QDialog(parent),
    project_settings(proj),
    ui(new Ui::SetupProjectDialogWindow)
{
    ui->setupUi(this);

    const double luminous_flux_to_watts_ratio = 683.0;
    units_items = {
        qMakePair(QString("W/m^2"), 1.0),
        qMakePair(QString("uW/cm^2"), 0.01),
        qMakePair(QString("lm/m^2"), 1.0 / luminous_flux_to_watts_ratio)
    };

    QPair<QString, double> each_pair;
    QStringList unitsNameItems;
    foreach(each_pair, units_items) {
        unitsNameItems.append(each_pair.first);
    }


   ui->unitsComboBox->addItems(unitsNameItems);

    const QStringList stepParalleItems = {"5", "10", "15", "45"};
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
    project_settings->radius = ui->radiusField->text().toDouble();
    QString unitsName =  ui->unitsComboBox->currentText();
    project_settings->units = unitsName;

    QPair<QString, double> each;
    foreach (each, units_items) {
        if (each.first == unitsName)
            project_settings->units_scale = each.second;
    }

    close();
}
