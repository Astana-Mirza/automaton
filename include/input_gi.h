#ifndef INPUTGI_H
#define INPUTGI_H

#include <element_gi.h>

class InputGI : public ElementGI
{
public:
     InputGI( QGraphicsScene *scene );
     QRectF boundingRect() const;
     bool empty() const;
     QString popData();

protected:
     void paint( QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * );
     void mouseMoveEvent( QGraphicsSceneMouseEvent *event );
     void mousePressEvent( QGraphicsSceneMouseEvent * );
     void mouseReleaseEvent( QGraphicsSceneMouseEvent * );

private:
     QStringList data_;
};

#endif // INPUTGI_H
