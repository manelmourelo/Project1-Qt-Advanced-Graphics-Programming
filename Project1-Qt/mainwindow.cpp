#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_transform.h"
#include <QMessageBox>
#include <iostream>
#include <QFileDialog>
#include "hierarchy.h"
#include "inspector.h"
#include "renderwidget.h"
#include "object.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_main_window(new Ui::MainWindow)
{
    ui_main_window->setupUi(this);

    //Signal & slot connections for the bar options
    connect(ui_main_window->actionNew_Scene, SIGNAL(triggered()), SLOT(OnNewSceneClicked()));
    connect(ui_main_window->actionSave, SIGNAL(triggered()), SLOT(OnSaveClicked()));
    connect(ui_main_window->actionFile, SIGNAL(triggered()), SLOT(OnOpenClicked()));
    connect(ui_main_window->actionExit, SIGNAL(triggered()), SLOT(OnExitClicked()));
    connect(ui_main_window->actionAbout, SIGNAL(triggered()), SLOT(OnAboutClicked()));

    hierarchy = new Hierarchy();
    ui_main_window->dockHierarchy->setWidget(hierarchy);

    inspector = new Inspector();
    ui_main_window->dockInspector->setWidget(inspector);

    connect(hierarchy, SIGNAL(EntitySelected(int, std::list<Object>)), inspector, SLOT(itemChanged(int, std::list<Object>)));
    connect(inspector, SIGNAL(FillColorChanged(QColor)), hierarchy, SLOT(FillColorChanged(QColor)));
    connect(inspector, SIGNAL(StrokeColorChanged(QColor)), hierarchy, SLOT(StrokeColorChanged(QColor)));
    connect(inspector, SIGNAL(NameChanged(QString)), hierarchy, SLOT(NameChanged(QString)));
    connect(inspector, SIGNAL(TransformXChanged(double)), hierarchy, SLOT(TransformXChanged(double)));
    connect(inspector, SIGNAL(TransformYChanged(double)), hierarchy, SLOT(TransformYChanged(double)));
    connect(inspector, SIGNAL(ScaleXChanged(double)), hierarchy, SLOT(ScaleXChanged(double)));
    connect(inspector, SIGNAL(ScaleYChanged(double)), hierarchy, SLOT(ScaleYChanged(double)));
    connect(inspector, SIGNAL(StrockeThicknessChanged(double)), hierarchy, SLOT(onStrockeThickness(double)));
    connect(inspector, SIGNAL(ShapeChanged(int)), hierarchy, SLOT(onShape(int)));
    connect(inspector, SIGNAL(StrokeStyleCHanged(int)), hierarchy, SLOT(onStrokeStyle(int)));
    connect(hierarchy, SIGNAL(ListIsEmpty()), inspector, SLOT(ListIsEmpty()));

    connect(this, SIGNAL(DeleteObjects()), hierarchy, SLOT(DeleteObjects()));

    renderWidget = new RenderWidget();
    QVBoxLayout *centralLayout = new QVBoxLayout();
    centralLayout->addWidget(renderWidget);
    ui_main_window->centralWidget->setLayout(centralLayout);

    //Connect for sending the list of objects to draw
    connect(hierarchy, SIGNAL(EntityToDraw(std::list<Object>)), renderWidget, SLOT(EntityToDraw(std::list<Object>)));


}

MainWindow::~MainWindow()
{
    delete ui_main_window;
}

void MainWindow::OnNewSceneClicked()
{

    QMessageBox::StandardButton button = QMessageBox::question(this,
                                                               "New scene",
                                                               "Do you want to start a new project from zero without saving changes?");
    if(button == QMessageBox::Yes){
        //TODO: Delete every object on scene
        emit DeleteObjects();
    }
    else{

    }
}

void MainWindow::OnSaveClicked()
{
    QMessageBox::StandardButton button = QMessageBox::question(this,
                                                               "Save",
                                                               "Do you want to save?");
    if(button == QMessageBox::Yes){
        std::cout << "Exit without saving changes" << std::endl;

        QString fileName = QFileDialog::getSaveFileName(this,
               tr("Save Proyect"), "",
               tr("QTProyect (*.qtProyect)"));

        if (fileName.isEmpty())
        {
                return;
        }
        else {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
                return;
            }

            QDataStream out(&file);
            out.setVersion(QDataStream::Qt_DefaultCompiledVersion);

            std::list<Object>::iterator it;

            out << (int)hierarchy->objects.size();

            for(it = hierarchy->objects.begin(); it != hierarchy->objects.end(); it++){
                out << it->name;
                out << it->position;
                out << it->scale;
                out << it->shape;
                out << it->fill_color;
                out << it->strocke_color;
                out << it->strocke_thickness;
                out << it->strocke_style;

            }


        }
    }
    else{
        std::cout << "Cancel exit" << std::endl;
    }
}
void MainWindow::OnOpenClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,   tr("Open Proyect"), "",
                                                tr("QTProyect (*.qtProyect)"));
    if (fileName.isEmpty())
            return;
        else {

            QFile file(fileName);

            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
                return;
            }

            QDataStream in(&file);
            in.setVersion(QDataStream::Qt_DefaultCompiledVersion);

            emit DeleteObjects();

            int number = 0;

            in >> number;


            for(int i = 0; i < number; ++i){
                hierarchy->onAddEntityClicked();
                in >>  hierarchy->objects.back().name;
                in >>  hierarchy->objects.back().position;
                in >>  hierarchy->objects.back().scale;
                in >>  hierarchy->objects.back().shape;
                in >>  hierarchy->objects.back().fill_color;
                in >>  hierarchy->objects.back().strocke_color;
                in >>  hierarchy->objects.back().strocke_thickness;
                in >>  hierarchy->objects.back().strocke_style;
            }


            emit hierarchy->EntityToDraw(hierarchy->objects);

    }


}

void MainWindow::OnExitClicked()
{
    QMessageBox::StandardButton button = QMessageBox::question(this,
                                                               "Exit application",
                                                               "Do you want to exit the aplication without saving the project?");
    if(button == QMessageBox::Yes){
        std::cout << "Exit without saving changes" << std::endl;
        this->close();
    }
    else{
        std::cout << "Cancel exit" << std::endl;
    }
}

void MainWindow::OnAboutClicked()
{

}
