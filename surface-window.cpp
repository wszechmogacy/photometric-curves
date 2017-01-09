#include <QImage>
#include <QPageLayout>
#include <QPainter>
#include <QPrintDialog>
#include <QPrinter>
#include <QSize>
#include <QtGui/QScreen>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#include <surface-graph.h>
#include <surface-window.h>


SurfaceWindow::SurfaceWindow(std::vector<Point> &data_table, unsigned columns_count, unsigned rows_count)
{
    graph_ = new Q3DSurface();
    QWidget *container = QWidget::createWindowContainer(graph_);

    if (!graph_->hasContext()) {
        QMessageBox msgBox;
        msgBox.setText("Couldn't initialize the OpenGL context.");
        msgBox.exec();
        //handle error
    }

    QSize screenSize = graph_->screen()->size();
    container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.6));
    container->setMaximumSize(screenSize);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    QVBoxLayout *vLayout = new QVBoxLayout();
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);
    vLayout->setAlignment(Qt::AlignTop);

    this->setWindowTitle(QStringLiteral("Photometric surface"));


    //add qsliders
        QSlider *rotationSliderX = new QSlider(Qt::Horizontal, this);
        rotationSliderX->setTickInterval(30);
        rotationSliderX->setTickPosition(QSlider::TicksBelow);
        rotationSliderX->setMinimum(-180);
        rotationSliderX->setValue(0);
        rotationSliderX->setMaximum(180);
        QSlider *rotationSliderY = new QSlider(Qt::Horizontal, this);
        rotationSliderY->setTickInterval(15);
        rotationSliderY->setTickPosition(QSlider::TicksAbove);
        rotationSliderY->setMinimum(-90);
        rotationSliderY->setValue(0);
        rotationSliderY->setMaximum(90);

        QPushButton *toPdfButton = new QPushButton;
        toPdfButton->setText(tr("Convert to PDF"));

        //add qsliders to right place in window
        vLayout->addWidget(new QLabel(tr("Rotate horizontally")));
        vLayout->addWidget(rotationSliderX, 0, Qt::AlignTop);
        vLayout->addWidget(new QLabel(tr("Rotate vertically")));
        vLayout->addWidget(rotationSliderY, 0, Qt::AlignTop);
        vLayout->addWidget(toPdfButton);


    SurfaceGraph *modifier = new SurfaceGraph(graph_, data_table, columns_count, rows_count);

    //connect sliders to slots
    QObject::connect(rotationSliderX, &QSlider::valueChanged, modifier, &SurfaceGraph::rotate_x);
    QObject::connect(rotationSliderY, &QSlider::valueChanged, modifier, &SurfaceGraph::rotate_y);
    QObject::connect(toPdfButton, &QPushButton::clicked, this, &SurfaceWindow::print_to_pdf);


    //set initial rotation of layer
    rotationSliderX->setValue(-130);
}

void SurfaceWindow::print_to_pdf()
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFileName("photometric_surface.pdf");
    printer.setOrientation(QPrinter::Landscape);
    printer.setResolution(300);

    QPrintDialog *dialog = new QPrintDialog(&printer);
    if (dialog->exec() == QDialog::Accepted) {

        QPainter painter;
        painter.begin(&printer);

        double xscale = printer.pageRect().width()/double(graph_->width());
                double yscale = printer.pageRect().height()/double(graph_->height());
                double scale = qMin(xscale, yscale);
                painter.translate(printer.paperRect().x() + printer.pageRect().width()/2,
                                   printer.paperRect().y() + printer.pageRect().height()/2);
                painter.scale(scale, scale);

        QImage img = graph_->renderToImage(0, QSize(graph_->width(),graph_->height()));

        painter.drawImage(-graph_->width() / 2, -graph_->height() / 2, img);
        painter.end();
    }
}
