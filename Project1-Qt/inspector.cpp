#include "inspector.h"
#include "ui_transform.h"
#include <QVBoxLayout>
#include "ui_color.h"
#include "ui_shape.h"
#include <QSpacerItem>

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

void Inspector::itemChanged(int new_item)
{

    switch(new_item){
    case 0:
        transform->show();
        form->hide();
        color->hide();
        break;
    case 1:
        transform->show();
        form->show();
        color->hide();
        break;
    case 2:
        transform->show();
        form->show();
        color->show();
        break;
    case 3:
        transform->hide();
        form->show();
        color->show();
        break;
    case 4:
        transform->hide();
        form->hide();
        color->show();
        break;
    default:
        transform->show();
        form->show();
        color->show();
        break;
    }

}
