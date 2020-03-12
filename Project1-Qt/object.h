#ifndef OBJECT_H
#define OBJECT_H
#include <string>
#include <QVector2D>
#include <QColor>
#include <QString>

enum Shape{
    Circle,
    Rectangle
};

class Object
{
public:
    Object();
    ~Object();

public:
    uint UUID = 0;

    QString name;

    QVector2D position;
    QVector2D scale;

    Shape shape;
    QColor fill_color;
    QColor strocke_color;
    float strocke_thickness;
    Qt::PenStyle strocke_style;

};

#endif // OBJECT_H
