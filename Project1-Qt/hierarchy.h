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

private:
    Ui::Hierarchy *ui;
public:
    std::list<Object> objects;
    std::list<Object> draw_order;
};

#endif // HIERARCHY_H
