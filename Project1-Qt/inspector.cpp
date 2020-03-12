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
#include <QString>
#include <QDebug>
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

    connect(ui_transform->nameInput, SIGNAL(returnPressed()), SLOT(onNameEntered()));

    connect(ui_transform->translationX, SIGNAL(valueChanged(double)), SLOT(onTransformX(double)));
    connect(ui_transform->translationY, SIGNAL(valueChanged(double)), SLOT(onTransformY(double)));
    connect(ui_transform->scaleX, SIGNAL(valueChanged(double)), SLOT(onScaleX(double)));
    connect(ui_transform->scaleY, SIGNAL(valueChanged(double)), SLOT(onScaleY(double)));

    connect(ui_color->strockeThickness, SIGNAL(valueChanged(double)), SLOT(onStrockeThickness(double)));

    connect(ui_form->shape, SIGNAL(currentIndexChanged(int)), SLOT(onShape(int)));

    connect(ui_color->strockeStyle, SIGNAL(currentIndexChanged(int)), SLOT(onStrokeStyle(int)));

    transform->hide();
    form->hide();
    color->hide();

}

Inspector::~Inspector()
{
    delete ui_transform;
    delete ui_form;
    delete ui_color;
}

QString getColorString(QColor color)
{
    int r = 0,g = 0,b = 0;
    color.getRgb(&r,&g,&b);

    QString string = "background-color: rgb(";
    string +=QString::number(r);
    string +=",";
    string +=QString::number(g);
    string +=",";
    string +=QString::number(b);
    string +=")";

    return string;
}

void Inspector::itemChanged(int new_item, std::list<Object> objects)
{
    if(objects.empty() == true){
        transform->hide();
        form->hide();
        color->hide();
    }
    else{
        transform->show();
        form->show();
        color->show();
    }
    std::list<Object>::iterator it;
    int i = 0;
    for(it = objects.begin(); it != objects.end(); it++){
        if(i == new_item){
            ui_transform->nameInput->setText(it->name);
            ui_transform->translationX->setValue(it->position.x());
            ui_transform->translationY->setValue(it->position.y());
            ui_transform->scaleX->setValue(it->scale.x());
            ui_transform->scaleY->setValue(it->scale.y());

            //FillColor
            QPalette pal = ui_color->fillColor->palette();
            QString string = getColorString(it->fill_color);
            ui_color->fillColor->setStyleSheet(string);
            ui_color->fillColor->setAutoFillBackground(true);
            ui_color->fillColor->setPalette(pal);
            ui_color->fillColor->update();
            //StrokeColor
            QPalette pal2 = ui_color->strockeColor->palette();
            QString string2 = getColorString(it->strocke_color);
            ui_color->strockeColor->setStyleSheet(string2);
            ui_color->strockeColor->setAutoFillBackground(true);
            ui_color->strockeColor->setPalette(pal2);
            ui_color->strockeColor->update();

            ui_color->strockeThickness->setValue(it->strocke_thickness);

            if(it->shape == Shape::Circle){
                ui_form->shape->setCurrentIndex(0);
            }
            else{
               ui_form->shape->setCurrentIndex(1);
            }

            if(it->strocke_style == Qt::PenStyle::SolidLine){
                ui_color->strockeStyle->setCurrentIndex(0);
            }
            else if(it->strocke_style == Qt::PenStyle::DashLine){
                ui_color->strockeStyle->setCurrentIndex(1);
            }
            else if(it->strocke_style == Qt::PenStyle::DotLine){
                ui_color->strockeStyle->setCurrentIndex(2);
            }
            else if(it->strocke_style == Qt::PenStyle::DashDotLine){
                ui_color->strockeStyle->setCurrentIndex(3);
            }
            else if(it->strocke_style == Qt::PenStyle::DashDotDotLine){
                ui_color->strockeStyle->setCurrentIndex(4);
            }
            else if(it->strocke_style == Qt::PenStyle::NoPen){
                ui_color->strockeStyle->setCurrentIndex(5);
            }

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

        QString string = getColorString(color);

        ui_color->fillColor->setStyleSheet(string);

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

        QString string = getColorString(color);

        ui_color->strockeColor->setStyleSheet(string);

        ui_color->strockeColor->setAutoFillBackground(true);
        ui_color->strockeColor->setPalette(pal);
        ui_color->strockeColor->update();

        emit StrokeColorChanged(color);
    }
}

void Inspector::onNameEntered()
{
    QString text = ui_transform->nameInput->text();
    emit NameChanged(text);
}

void Inspector::onTransformX(double d){
    emit TransformXChanged(d);
}

void Inspector::onTransformY(double d){
    emit TransformYChanged(d);
}

void Inspector::onScaleX(double d){
    emit ScaleXChanged(d);
}

void Inspector::onScaleY(double d){
    emit ScaleYChanged(d);
}

void Inspector::onStrockeThickness(double d){
    emit StrockeThicknessChanged(d);
}

void Inspector::onShape(int index){
    emit ShapeChanged(index);
}

void Inspector::onStrokeStyle(int index){
    emit StrokeStyleCHanged(index);
}

