#include <automaton_gi.h>
#include <connector_gi.h>

ConnectorGI::ConnectorGI( AutomatonGI* automaton ):
     automaton_( automaton )
{}


QRectF ConnectorGI::boundingRect() const
{
     return QRectF( -15, -15, 30, 30 );
}


void ConnectorGI::paint( QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * )
{
     painter->setPen( Qt::black );
     painter->setBrush( Qt::blue );
     painter->drawEllipse( -15, -15, 30, 30 );
}

