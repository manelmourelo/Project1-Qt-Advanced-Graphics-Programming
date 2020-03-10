#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <QWidget>
#include <list>
#include "object.h"

namespace Ui {
class Hierarchy;
}

class Hierarchy : public QWidget
{
    Q_OBJECT

public:
    explicit Hierarchy(QWidget *parent = nullptr);
    ~Hierarchy();

signals:
    void EntitySelected(int entotyID, std::list<Object> objects);

public slots:
    void onAddEntityClicked();
    void onRemoveEntityClicked();
    void onItemSelected(int id);
    void FillColorChanged(QColor);
    void StrokeColorChanged(QColor);
    void NameChanged(QString text);
    void TransformXChanged(double d);
    void TransformYChanged(double d);
    void ScaleXChanged(double d);
    void ScaleYChanged(double d);
    void onStrockeThickness(double d);
    void onShape(int index);
    void onStrokeStyle(int index);

private:
    Ui::Hierarchy *ui;
public:
    std::list<Object> objects;
    std::list<Object> draw_order;
    Object* current_object = nullptr;
};

#endif // HIERARCHY_H
