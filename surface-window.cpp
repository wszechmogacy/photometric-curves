#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtGui/QScreen>

#include "surface-window.h"
#include "surface-graph.h"

SurfaceWindow::SurfaceWindow(std::vector<Point> &data_table, unsigned columns_count, unsigned rows_count)
{
    Q3DSurface *graph = new Q3DSurface();
    QWidget *container = QWidget::createWindowContainer(graph);

    if (!graph->hasContext()) {
        QMessageBox msgBox;
        msgBox.setText("Couldn't initialize the OpenGL context.");
        msgBox.exec();
        //handle error
    }

    QSize screenSize = graph->screen()->size();
    container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.6));
    container->setMaximumSize(screenSize);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);

    QWidget *widget = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);
    vLayout->setAlignment(Qt::AlignTop);

    widget->setWindowTitle(QStringLiteral("Photometric surface"));


    //add qsliders
        QSlider *rotationSliderX = new QSlider(Qt::Horizontal, widget);
        rotationSliderX->setTickInterval(30);
        rotationSliderX->setTickPosition(QSlider::TicksBelow);
        rotationSliderX->setMinimum(-180);
        rotationSliderX->setValue(0);
        rotationSliderX->setMaximum(180);
        QSlider *rotationSliderY = new QSlider(Qt::Horizontal, widget);
        rotationSliderY->setTickInterval(15);
        rotationSliderY->setTickPosition(QSlider::TicksAbove);
        rotationSliderY->setMinimum(-90);
        rotationSliderY->setValue(0);
        rotationSliderY->setMaximum(90);

        QPushButton *toPdfButton = new QPushButton;
        toPdfButton->setText("Convert to PDF");

        //add qsliders to right place in window
        vLayout->addWidget(new QLabel(QStringLiteral("Rotate horizontally")));
        vLayout->addWidget(rotationSliderX, 0, Qt::AlignTop);
        vLayout->addWidget(new QLabel(QStringLiteral("Rotate vertically")));
        vLayout->addWidget(rotationSliderY, 0, Qt::AlignTop);
        vLayout->addWidget(toPdfButton);


    SurfaceGraph *modifier = new SurfaceGraph(graph, data_table, columns_count, rows_count);

    //connect sliders to slots
    QObject::connect(rotationSliderX, &QSlider::valueChanged, modifier, &SurfaceGraph::rotateX);
    QObject::connect(rotationSliderY, &QSlider::valueChanged, modifier, &SurfaceGraph::rotateY);
    QObject::connect(toPdfButton, &QPushButton::clicked, modifier, &SurfaceGraph::print_to_pdf);

    //set initial rotation of layer
    rotationSliderX->setValue(-130);

     widget->show();

}
