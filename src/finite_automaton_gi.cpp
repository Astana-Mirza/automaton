#include <finite_automaton_gi.h>

FiniteAutomatonGI::FiniteAutomatonGI( const std::string& init_state,
                                      const std::string& tr_file,
                                      const std::string& tr_func_name,
                                      const std::string& out_file,
                                      const std::string& out_func_name,
                                      size_t index ) :
     AutomatonGI( index ),
     processor_( init_state, { tr_file, tr_func_name }, { out_file, out_func_name } ) {}


void FiniteAutomatonGI::show_info() const
{

}
