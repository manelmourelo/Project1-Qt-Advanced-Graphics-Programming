#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <QWidget>

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
    void EntitySelected(int entotyID);

public slots:
    void onAddEntityClicked();
    void onRemoveEntityClicked();
    void onItemSelected(int id);

private:
    Ui::Hierarchy *ui;
};

#endif // HIERARCHY_H
