#ifndef SETUPPROJECTDIALOGWINDOW_H
#define SETUPPROJECTDIALOGWINDOW_H

#include <QDialog>

namespace Ui {
class SetupProjectDialogWindow;
}

class SetupProjectDialogWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SetupProjectDialogWindow(QWidget *parent = 0);
    ~SetupProjectDialogWindow();

private slots:
    void on_startProjectButton_clicked();

private:
    Ui::SetupProjectDialogWindow *ui;
};

#endif // SETUPPROJECTDIALOGWINDOW_H
