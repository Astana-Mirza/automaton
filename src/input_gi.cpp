#include <automaton_gi.h>
#include <input_gi.h>
#include <QPainter>
#include <QCursor>

InputGI::InputGI()
{

}


QRectF InputGI::boundingRect() const
{
     return QRectF( -25, -25, 50, 50 );
}


void InputGI::paint( QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * )
{
     QPolygon polygon;
     polygon << QPoint( -25, -25 ) << QPoint( -25, 25 ) << QPoint( 25, 0 );
	painter->setPen( Qt::black );
	painter->setBrush( Qt::red );
	painter->drawPolygon( polygon );
}


void InputGI::mouseMoveEvent( QGraphicsSceneMouseEvent *event )
{
     setPos( event->scenePos().x(), event->scenePos().y() );
}


void InputGI::mousePressEvent( QGraphicsSceneMouseEvent * )
{
     setCursor( QCursor( Qt::ClosedHandCursor ) );
}


void InputGI::mouseReleaseEvent( QGraphicsSceneMouseEvent * )
{
     setCursor( QCursor( Qt::ArrowCursor ) );
     auto colliding = collidingItems( Qt::IntersectsItemBoundingRect );
     if ( is_input_set() )
     {
          get_input()->set_output( nullptr );
     }
     set_input( nullptr );
     if ( is_output_set() )
     {
          get_output()->set_input( nullptr );
     }
     set_output( nullptr );
     for ( QGraphicsItem* item : colliding )
     {
          AutomatonGI* automaton = dynamic_cast<AutomatonGI*>( item );
          if ( !automaton )
          {
               continue;
          }
          if ( automaton->scenePos().x() >= scenePos().x() && !automaton->is_input_set() )
          {
               automaton->set_input( this );
               setPos( automaton->scenePos().x() - ( boundingRect().width() / 4 ) - ( automaton->boundingRect().width() / 2 ),
                       automaton->scenePos().y() );
               set_output( automaton );
               break;
          }
     }
     update();
}
