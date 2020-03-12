#include "renderwidget.h"
#include <QPainter>
#include "qtextstream.h"

RenderWidget::RenderWidget()
{
    setAutoFillBackground(true);
}

RenderWidget::~RenderWidget()
{

}

QSize RenderWidget::sizeHint() const
{
    return QSize(256, 256);
}

QSize RenderWidget::minimumSizeHint() const
{
    return QSize(64, 64);
}

void RenderWidget::paintEvent(QPaintEvent *event)
{
     QColor blueColor = QColor::fromRgb(127, 190, 220);

     //Prepare the painter for this widget
     QPainter painter(this);

     QBrush brush;
     QPen pen;

     //Brush/Pen configuration
     brush.setColor(blueColor);
     brush.setStyle(Qt::BrushStyle::SolidPattern);
     pen.setStyle(Qt::PenStyle::NoPen);
     painter.setBrush(brush);
     painter.setPen(pen);

     //Paint background
     painter.drawRect(rect());

     std::list<Object>::iterator it;
     for(it = objects_to_draw.begin(); it != objects_to_draw.end(); it++){
         //Brush/Pen configuration
         brush.setColor(it->fill_color);
         pen.setWidth(it->strocke_thickness);
         pen.setColor(it->strocke_color);
         pen.setStyle(it->strocke_style);
         painter.setBrush(brush);
         painter.setPen(pen);

         //DrawCircle
         int r = (int)64;
         int w = (int)it->scale.x()*r;
         int h = (int)it->scale.y()*r;
         int x = (int)it->position.x();
         int y = (int)it->position.y();
         QRect shape(x,y,w,h);

         if(it->shape == Shape::Circle)
            painter.drawEllipse(shape);
         else
            painter.drawRect(shape);
     }
 }


void RenderWidget::EntityToDraw(std::list<Object> objects){
    objects_to_draw.clear();
    objects_to_draw = objects;
    update();
}
