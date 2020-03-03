#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H

#include <QWidget>

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

private:
    void paintEvent(QPaintEvent *event) override;

};

#endif // RENDERWIDGET_H
