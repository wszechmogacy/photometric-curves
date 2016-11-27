#include "setup-project-dialog-window.h"
#include "ui_setup-project-dialog-window.h"

SetupProjectDialogWindow::SetupProjectDialogWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetupProjectDialogWindow)
{
    ui->setupUi(this);
}

SetupProjectDialogWindow::~SetupProjectDialogWindow()
{
    delete ui;
}
