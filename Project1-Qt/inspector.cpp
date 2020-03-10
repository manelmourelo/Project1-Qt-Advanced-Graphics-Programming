#include "inspector.h"
#include "ui_transform.h"
#include <QVBoxLayout>
#include "ui_color.h"
#include "ui_shape.h"
#include <QSpacerItem>
#include "hierarchy.h"
#include "object.h"
#include <list>
#include <QColorDialog>
#include <QPalette>

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

    connect(ui_color->fillColor, SIGNAL(clicked()), SLOT(onColorClicked()));
    connect(ui_color->strockeColor, SIGNAL(clicked()), SLOT(onStrokeColorClicked()));

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

void Inspector::onColorClicked(){
    QColor color = QColorDialog::getColor(Qt::yellow, this );
    if( color.isValid() )
    {
        QPalette pal = ui_color->fillColor->palette();
        pal.setColor(QPalette::Button, color);
        ui_color->fillColor->setAutoFillBackground(true);
        ui_color->fillColor->setPalette(pal);
        ui_color->fillColor->update();
        emit FillColorChanged(color);
    }
}
void Inspector::onStrokeColorClicked(){
    QColor color = QColorDialog::getColor(Qt::yellow, this );
    if( color.isValid() )
    {
        QPalette pal = ui_color->strockeColor->palette();
        pal.setColor(QPalette::Button, color);
        ui_color->strockeColor->setAutoFillBackground(true);
        ui_color->strockeColor->setPalette(pal);
        ui_color->strockeColor->update();
        emit StrokeColorChanged(color);
    }
}
