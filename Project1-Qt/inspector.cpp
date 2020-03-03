#include "inspector.h"
#include "ui_transform.h"
#include <QVBoxLayout>
#include "ui_color.h"
#include "ui_shape.h"
#include <QSpacerItem>
#include "hierarchy.h"
#include "object.h"
#include <list>

Inspector::Inspector(QWidget *parent) : QWidget(parent)
{
    ui_transform = new Ui::Transform();
    ui_form = new Ui::Form();
    ui_color = new Ui::Color();

    //Create widget
    transform = new QWidget;
    ui_transform->setupUi(transform);
    //Create widget 2
    form = new QWidget;
    ui_form->setupUi(form);
    //Create widget 3
    color = new QWidget;
    ui_color->setupUi(color);

    //Create, fill and set layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(transform);
    QSpacerItem *spacer = new QSpacerItem(1,1,QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(form);
    layout->addWidget(color);
    layout->addItem(spacer);
    //...
    setLayout(layout);

}

Inspector::~Inspector()
{
    delete ui_transform;
    delete ui_form;
    delete ui_color;
}

void Inspector::itemChanged(int new_item, std::list<Object> objects)
{

    std::list<Object>::iterator it;
    int i = 0;
    for(it = objects.begin(); it != objects.end(); it++){
        if(i == new_item){
            ui_transform->translationX->setValue(it->position.x());
            ui_transform->translationY->setValue(it->position.y());
            ui_transform->scaleX->setValue(it->scale.x());
            ui_transform->scaleY->setValue(it->scale.y());
            break;
        }
        i++;
    }
}
