#ifndef AUTOMATON_GI_H
#define AUTOMATON_GI_H

#include <python_function.h>
#include <element_gi.h>
#include <connector_gi.h>

class AutomatonGI: public ElementGI
{
public:
     AutomatonGI( size_t index = 0 );
     ~AutomatonGI();

     void set_output( ElementGI* output );
     QRectF boundingRect() const;
     uint32_t get_automaton_index() const { return automaton_index_; }

protected:
     size_t automaton_index_;
     ConnectorGI* connector_;

     void paint( QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * );
     void mouseMoveEvent( QGraphicsSceneMouseEvent *event );
     void mousePressEvent( QGraphicsSceneMouseEvent *event );
     void mouseReleaseEvent( QGraphicsSceneMouseEvent *event );

     bool check_input_colliding( QGraphicsItem* item );
     virtual void show_info() const = 0;
};

#endif // AUTOMATON_GI_H
