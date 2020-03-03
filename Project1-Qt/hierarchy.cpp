#include "hierarchy.h"
#include "ui_hierarchy.h"

Hierarchy::Hierarchy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hierarchy)
{
    ui->setupUi(this);

    connect(ui->addEntityButton, SIGNAL(clicked()), SLOT(onAddEntityClicked()));
    connect(ui->removeEntityButton, SIGNAL(clicked()), SLOT(onRemoveEntityClicked()));
    connect(ui->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(onItemSelected(int)));

}

Hierarchy::~Hierarchy()
{
    delete ui;
}

void Hierarchy::onAddEntityClicked()
{
    ui->listWidget->addItem("Enity");
}
void Hierarchy::onRemoveEntityClicked()
{
    int current = ui->listWidget->currentRow();
    ui->listWidget->takeItem(current);
}

void Hierarchy::onItemSelected(int id)
{
    emit EntitySelected(id);
}
