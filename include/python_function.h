#ifndef PYTHON_FUNCTION_H
#define PYTHON_FUNCTION_H

#include <pybind11/pybind11.h>
#include <string>

template < typename Out >
class PythonFunction
{
public:
     PythonFunction( const std::string& file, const std::string& func_name );
     void set_function( const std::string& file, const std::string& func_name );

     template < typename ...Args >
     Out operator()( Args ...args ) const;

private:
     pybind11::function func_;
};

//-----------------------------------------IMPLEMENTATION------------------------------------------

template < typename Out >
PythonFunction< Out >::PythonFunction( const std::string& file, const std::string& func_name )
{
     set_function( file, func_name );
}


template < typename Out >
void PythonFunction< Out >::set_function( const std::string& file, const std::string& func_name )
{
     auto util = pybind11::module_::import( "importlib.util" );
     auto spec = util.attr( "spec_from_file_location" )( "", file.c_str() );
     auto module = util.attr( "module_from_spec" )( spec );
     spec.attr( "loader" ).attr( "exec_module" )( module );
     func_ = pybind11::reinterpret_borrow< pybind11::function >( module.attr( func_name.c_str() ) );
}


template < typename Out >
template < typename ...Args >
Out PythonFunction< Out >::operator()( Args ...args ) const
{
     pybind11::object ret = func_( args... );
     return ret.cast< Out >();
}

#endif // PYTHON_FUNCTION_H
