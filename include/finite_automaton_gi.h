#ifndef FINITE_AUTOMATON_GI_H
#define FINITE_AUTOMATON_GI_H

#include <automaton_gi.h>
#include <automaton/finite_automaton.h>

class FiniteAutomatonGI : public AutomatonGI
{
public:
     using automaton_type = FiniteAutomaton< std::string, std::string, std::string,
                                             PythonFunction< std::string >,
                                             PythonFunction< std::string > >;
     explicit FiniteAutomatonGI( const std::string& init_state,
                           const std::string& tr_file,
                           const std::string& tr_func_name,
                           const std::string& out_file,
                           const std::string& out_func_name,
                           size_t index );

private:
     automaton_type processor_;

     void show_info() const;
};

#endif // FINITE_AUTOMATON_GI_H
