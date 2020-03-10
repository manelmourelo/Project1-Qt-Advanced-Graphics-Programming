#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>
#include "object.h"

namespace Ui {
    class Transform;
    class Form;
    class Color;
}

class Inspector : public QWidget
{
    Q_OBJECT

public:
    explicit Inspector(QWidget *parent = nullptr);
    ~Inspector();

signals:
    void FillColorChanged(QColor);
    void StrokeColorChanged(QColor);
    void NameChanged(QString);
    void TransformXChanged(double d);
    void TransformYChanged(double d);
    void ScaleXChanged(double d);
    void ScaleYChanged(double d);
    void StrockeThicknessChanged(double d);
    void ShapeChanged(int index);
    void StrokeStyleCHanged(int index);

public slots:
    void itemChanged(int new_item, std::list<Object> object);
    void onColorClicked();
    void onStrokeColorClicked();
    void onNameEntered();
    void onTransformX(double d);
    void onTransformY(double d);
    void onScaleX(double d);
    void onScaleY(double d);
    void onStrockeThickness(double d);
    void onShape(int index);
    void onStrokeStyle(int index);

private:
     Ui::Transform *ui_transform;
     QWidget *transform;

     Ui::Form *ui_form;
     QWidget *form;

     Ui::Color *ui_color;
     QWidget *color;

};

#endif // INSPECTOR_H
