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

    renderWidget = new RenderWidget();
    QVBoxLayout *centralLayout = new QVBoxLayout();
    centralLayout->addWidget(renderWidget);
    ui_main_window->centralWidget->setLayout(centralLayout);


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
    }
    else{
        std::cout << "Cancel exit" << std::endl;
    }
}
void MainWindow::OnOpenClicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Open Project");
    if(!path.isEmpty()){
        std::cout << path.toStdString() << std::endl;
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
