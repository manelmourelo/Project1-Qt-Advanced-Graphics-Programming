#include "hierarchy.h"
#include "ui_hierarchy.h"
#include "object.h"
#include <QTextStream>

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
    int new_current =  ui->listWidget->currentRow();

    int i = 0;
    int current_UUID = 0;

    std::list<Object>::iterator it;
    for(it = objects.begin(); it != objects.end(); it++){
        if(i == current){
            current_UUID = it->UUID;
            current_object = nullptr;
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

    int j = 0;
    std::list<Object>::iterator it3;
    for(it3 = objects.begin(); it3 != objects.end(); it3++){
        if(j == new_current){
            current_object = &(*it3);
            emit EntitySelected(j, objects);
            break;
        }
    }

}

void Hierarchy::onItemSelected(int id)
{
    int i = 0;
    std::list<Object>::iterator it;
    for(it = objects.begin(); it != objects.end(); it++){
        if(i == id){
            current_object = &(*it);
            break;
        }
        i++;
    }
    emit EntitySelected(id, objects);
}

void Hierarchy::FillColorChanged(QColor color){
    if(current_object != nullptr){
        current_object->fill_color = color;
    }
}
void Hierarchy::StrokeColorChanged(QColor color){
    if(current_object != nullptr){
        current_object->strocke_color = color;
    }
}

void Hierarchy::NameChanged(QString text){
    if(current_object != nullptr){
        QTextStream ts(stderr);
        ts << text;
        current_object->name = text;
    }
}

void Hierarchy::TransformXChanged(double d){
    if(current_object != nullptr){
        current_object->position.setX(d);
    }
}

void Hierarchy::TransformYChanged(double d){
    if(current_object != nullptr){
        current_object->position.setY(d);
    }
}

void Hierarchy::ScaleXChanged(double d){
    if(current_object != nullptr){
        current_object->scale.setX(d);
    }
}

void Hierarchy::ScaleYChanged(double d){
    if(current_object != nullptr){
        current_object->scale.setY(d);
    }
}

void Hierarchy::onStrockeThickness(double d){
    if(current_object != nullptr){
        current_object->strocke_thickness = d;
    }
}

void Hierarchy::onShape(int index){
    if(current_object != nullptr){
        if(index == 0){
            current_object->shape = Shape::Circle;
        }
        else{
            current_object->shape = Shape::Rectangle;
        }
    }
}

void Hierarchy::onStrokeStyle(int index){
    if(current_object != nullptr){
        if(index == 0){
            current_object->strocke_style = Qt::PenStyle::SolidLine;
        }
        else if(index == 1){
            current_object->strocke_style = Qt::PenStyle::DashLine;
        }
        else if(index == 2){
            current_object->strocke_style = Qt::PenStyle::DotLine;
        }
        else if(index == 3){
            current_object->strocke_style = Qt::PenStyle::DashDotLine;
        }
        else if(index == 4){
            current_object->strocke_style = Qt::PenStyle::DashDotDotLine;
        }
        else if(index == 5){
            current_object->strocke_style = Qt::PenStyle::NoPen;
        }
    }
}

