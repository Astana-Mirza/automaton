#include <automaton_gi.h>
#include <connector_gi.h>

ConnectorGI::ConnectorGI( AutomatonGI* result_automaton ):
    result_automaton_( result_automaton )
{}

ConnectorGI::~ConnectorGI()
{}

QRectF ConnectorGI::boundingRect() const
{
    return QRectF(-15, -15, 30, 30);
}

void ConnectorGI::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::blue);
    painter->drawEllipse(  -15, -15, 30, 30 );
}

