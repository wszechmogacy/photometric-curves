#include "introduction-dialog-window.h"
#include "ui_introduction-dialog-window.h"

IntroductionDialogWindow::IntroductionDialogWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IntroductionDialogWindow)
{
    ui->setupUi(this);
}

IntroductionDialogWindow::~IntroductionDialogWindow()
{
    delete ui;
}
