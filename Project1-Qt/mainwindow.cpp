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

    connect(ui_main_window->actionSave, SIGNAL(triggered()), SLOT(OnSaveClicked()));
    connect(ui_main_window->actionFile, SIGNAL(triggered()), SLOT(OnOpenClicked()));

    hierarchy = new Hierarchy();
    ui_main_window->dockHierarchy->setWidget(hierarchy);

    inspector = new Inspector();
    ui_main_window->dockInspector->setWidget(inspector);

    connect(hierarchy, SIGNAL(EntitySelected(int, std::list<Object>)), inspector, SLOT(itemChanged(int, std::list<Object>)));

    renderWidget = new RenderWidget();
    QVBoxLayout *centralLayout = new QVBoxLayout();
    centralLayout->addWidget(renderWidget);
    ui_main_window->centralWidget->setLayout(centralLayout);


}

MainWindow::~MainWindow()
{
    delete ui_main_window;
}

void MainWindow::OnSaveClicked()
{
    QMessageBox::StandardButton button = QMessageBox::question(this,
                                                               "Exit application",
                                                               "Do you want to exit the aplication without saving the project?");
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
