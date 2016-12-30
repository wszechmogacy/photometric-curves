#include "setup-project-dialog-window.h"
#include "ui_setup-project-dialog-window.h"

SetupProjectDialogWindow::SetupProjectDialogWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetupProjectDialogWindow)
{
    ui->setupUi(this);

    //connect(this, SIGNAL(close()), this->parent(), SLOT(destroy()));

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
    close();
}
