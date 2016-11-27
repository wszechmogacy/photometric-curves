#ifndef INTRODUCTIONDIALOGWINDOW_H
#define INTRODUCTIONDIALOGWINDOW_H

#include <QDialog>

namespace Ui {
class IntroductionDialogWindow;
}

class IntroductionDialogWindow : public QDialog
{
    Q_OBJECT

public:
    explicit IntroductionDialogWindow(QWidget *parent = 0);
    ~IntroductionDialogWindow();

private slots:
    void on_createProjectButton_clicked();

private:
    Ui::IntroductionDialogWindow *ui;
};

#endif // INTRODUCTIONDIALOGWINDOW_H
