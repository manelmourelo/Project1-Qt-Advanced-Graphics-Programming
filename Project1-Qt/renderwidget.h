#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H

#include <QWidget>
#include "object.h"

class RenderWidget : public QWidget
{
     Q_OBJECT

public:
    RenderWidget();
    ~RenderWidget();

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

signals:

public slots:
    void EntityToDraw(std::list<Object> objects);

private:
    void paintEvent(QPaintEvent *event) override;
    std::list<Object> objects_to_draw;

};

#endif // RENDERWIDGET_H
