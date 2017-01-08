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
    project_settings->student_name_ = ui->studentNameField->text();
    project_settings->class_date_ = ui->classesDateField->text();
    project_settings->student_group_ = ui->studentGroupField->text();
    project_settings->source_name_ = ui->lightSourceField->text();
    project_settings->step_in_parallel_dir_ = ui->stepParallelComboBox->currentText().toUInt();
    project_settings->step_in_meridian_dir_ = ui->stepInMeridianComboBox->currentText().toUInt();
    project_settings->radius_ = ui->radiusField->text().toDouble();
    QString unitsName =  ui->unitsComboBox->currentText();
    project_settings->units_ = unitsName;

    QPair<QString, double> each;
    foreach (each, units_items) {
        if (each.first == unitsName)
            project_settings->units_scale_ = each.second;
    }

    close();
}
