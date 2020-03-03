#ifndef OBJECT_H
#define OBJECT_H
#include <string>
#include <QVector2D>
#include <QColor>

enum Shape{
    Circle,
    Rectangle,
    Triangle
};

class Object
{
public:
    Object();
    ~Object();

public:
    uint UUID = 0;

    std::string name;

    QVector2D position;
    QVector2D scale;

    Shape shape;
    float size;
    QColor fill_color;
    QColor strocke_color;
    float strocke_thickness;
    Qt::PenStyle strocke_style;

};

#endif // OBJECT_H
