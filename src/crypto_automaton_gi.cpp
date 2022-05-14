#include <crypto_automaton_gi.h>
#include <QPainter>

CryptoAutomatonGI::CryptoAutomatonGI( const std::string& init_state,
                                      const std::string& init_key,
                                      const std::string& tr_file,
                                      const std::string& tr_func_name,
                                      const std::string& out_file,
                                      const std::string& out_func_name,
                                      size_t index ) :
     AutomatonGI( index ),
     processor_( init_state, init_key, { tr_file, tr_func_name }, { out_file, out_func_name } ) {}


void CryptoAutomatonGI::show_info() const
{

}

void CryptoAutomatonGI::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
     AutomatonGI::paint( painter, option, widget );
     QPolygon polygon;
     polygon << QPoint( -23, -10 ) << QPoint( -15, -10 ) << QPoint( -19, -18 );
     painter->drawPolygon( polygon );
     painter->drawRect( -25, -20, 12, 12 );
     painter->drawArc( QRectF{ -24, -25, 10, 10 }, 0, 2880 );
}
