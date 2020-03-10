#include "hierarchy.h"
#include "ui_hierarchy.h"
#include "object.h"

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
    Object new_object = Object();
    if(objects.size() >= 0){
        new_object.UUID = 0;
    }
    else{
        new_object.UUID = objects.back().UUID+1;
    }
    objects.push_back(new_object);
    draw_order.push_back(new_object);
    ui->listWidget->addItem("NewObject");
}
void Hierarchy::onRemoveEntityClicked()
{
    int current = ui->listWidget->currentRow();
    ui->listWidget->takeItem(current);

    int i = 0;
    int current_UUID = 0;

    std::list<Object>::iterator it;
    for(it = objects.begin(); it != objects.end(); it++){
        if(i == current){
            current_UUID = it->UUID;
            objects.erase(it);
            break;
        }
        i++;
    }
    std::list<Object>::iterator it2;
    for(it2 = draw_order.begin(); it2 != draw_order.end(); it2++){
        if(it2->UUID == current_UUID){
            draw_order.erase(it2);
            break;
        }
    }
}

void Hierarchy::onItemSelected(int id)
{
    emit EntitySelected(id, objects);
}

void Hierarchy::FillColorChanged(QColor color){
     current_object->fill_color = color;
}
void Hierarchy::StrokeColorChanged(QColor color){
    current_object->strocke_color = color;
}
