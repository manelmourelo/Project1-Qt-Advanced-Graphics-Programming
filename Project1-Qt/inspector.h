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

public slots:
    void itemChanged(int new_item, std::list<Object> object);

private:
     Ui::Transform *ui_transform;
     QWidget *transform;

     Ui::Form *ui_form;
     QWidget *form;

     Ui::Color *ui_color;
     QWidget *color;

};

#endif // INSPECTOR_H
