#include <QWidget>
#include <QTranslator>

#include <introduction-dialog-window.h>
#include <project-settings.h>
#include <setup-project-dialog-window.h>
#include <ui_introduction-dialog-window.h>

IntroductionDialogWindow::IntroductionDialogWindow(ProjectSettings *proj_settings, QTranslator *translator, QWidget *parent) :
    QDialog(parent),
    ui_(new Ui::IntroductionDialogWindow),
    project_settings_(proj_settings),
    translator(translator)
{
    ui_->setupUi(this);
    setWindowTitle(tr("Photometric Curves"));
    ui_->createProjectButton->setText(tr("Create Project"));
    ui_->openProjectButton->setText(tr("Open Project"));

    QStringList languages = {"English", "Polski"};
    ui_->languagecomboBox->addItems(languages);
    auto language = QLocale::system().name();
    if (language == "pl_PL") {
        ui_->languagecomboBox->setCurrentIndex(1);
    } else {
        ui_->languagecomboBox->setCurrentIndex(0);
    }
}

IntroductionDialogWindow::~IntroductionDialogWindow()
{
    delete ui_;
}

void IntroductionDialogWindow::on_createProjectButton_clicked()
{
    if (ui_->languagecomboBox->currentText() == "Polski") {
        translator->load("photometric-curves-pl_PL.qm");
        QApplication::instance()->installTranslator(translator);
    } else {
        QApplication::instance()->removeTranslator(translator);
    }

    SetupProjectDialogWindow window(project_settings_);
    window.exec();
    close();
}
