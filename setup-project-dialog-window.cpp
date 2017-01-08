#include <QWidget>

#include <project-settings.h>
#include <setup-project-dialog-window.h>
#include <ui_setup-project-dialog-window.h>


SetupProjectDialogWindow::SetupProjectDialogWindow(ProjectSettings *proj, QWidget *parent) :
    QDialog(parent),
    project_settings_(proj),
    ui_(new Ui::SetupProjectDialogWindow)
{
    ui_->setupUi(this);
    const double luminous_flux_to_watts_ratio = 683.0;
    units_items_ = {
        qMakePair(QString("W/m^2"), 1.0),
        qMakePair(QString("uW/cm^2"), 0.01),
        qMakePair(QString("lm/m^2"), 1.0 / luminous_flux_to_watts_ratio)
    };

    QPair<QString, double> each_pair;
    QStringList unitsNameItems;
    foreach(each_pair, units_items_) {
        unitsNameItems.append(each_pair.first);
    }


   ui_->unitsComboBox->addItems(unitsNameItems);

    const QStringList stepParalleItems = {"5", "10", "15", "45"};
    ui_->stepParallelComboBox->addItems(stepParalleItems);
    ui_->stepInMeridianComboBox->addItems(stepParalleItems);
}

SetupProjectDialogWindow::~SetupProjectDialogWindow()
{
    delete ui_;
}

void SetupProjectDialogWindow::on_startProjectButton_clicked()
{
    project_settings_->student_name_ = ui_->studentNameField->text();
    project_settings_->class_date_ = ui_->classesDateField->text();
    project_settings_->student_group_ = ui_->studentGroupField->text();
    project_settings_->source_name_ = ui_->lightSourceField->text();
    project_settings_->step_in_parallel_dir_ = ui_->stepParallelComboBox->currentText().toUInt();
    project_settings_->step_in_meridian_dir_ = ui_->stepInMeridianComboBox->currentText().toUInt();
    project_settings_->radius_ = ui_->radiusField->text().toDouble();
    QString unitsName =  ui_->unitsComboBox->currentText();
    project_settings_->units_ = unitsName;

    QPair<QString, double> each;
    foreach (each, units_items_) {
        if (each.first == unitsName)
            project_settings_->units_scale_ = each.second;
    }

    close();
}
