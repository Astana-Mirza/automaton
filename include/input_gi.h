#ifndef INPUTGI_H
#define INPUTGI_H

#include <element_gi.h>

class InputGI : public ElementGI
{
public:
     InputGI();
     QRectF boundingRect() const;

protected:
     void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );
     void mouseMoveEvent( QGraphicsSceneMouseEvent *event );
     void mousePressEvent( QGraphicsSceneMouseEvent *event );
     void mouseReleaseEvent( QGraphicsSceneMouseEvent *event );
};

#endif // INPUTGI_H
