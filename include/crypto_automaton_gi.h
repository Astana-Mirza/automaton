#ifndef CRYPTO_AUTOMATON_GI_H
#define CRYPTO_AUTOMATON_GI_H

#include <automaton_gi.h>
#include <automaton/crypto_automaton.h>

class CryptoAutomatonGI : public AutomatonGI
{
public:
     using automaton_type = CryptoAutomaton< std::string, std::string, std::string,
                                             PythonFunction< std::string >,
                                             PythonFunction< std::string >, std::string >;
     explicit CryptoAutomatonGI( QGraphicsScene *scene,
                           const std::string& init_state,
                           const std::string& init_key,
                           const std::string& tr_file,
                           const std::string& tr_func_name,
                           const std::string& out_file,
                           const std::string& out_func_name,
                           size_t index );
     std::string step( const std::string& data );

private:
     automaton_type processor_;

     void show_info() const;
     void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );
};

#endif // CRYPTO_AUTOMATON_GI_H
