#include "object.h"

Object::Object()
{
    name = QString("NewObject");

    position = QVector2D(0.0f,0.0f);
    scale = QVector2D(1.0f,1.0f);

    shape = Shape::Circle;
    fill_color = QColor(1.0f,1.0f,1.0f);
    strocke_color = QColor(0.0f,0.0f,0.0f);
    strocke_thickness = 5.0f;
    strocke_style = Qt::PenStyle::SolidLine;
}

Object::~Object()
{
}
