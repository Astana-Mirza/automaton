#ifndef PYTHON_FUNCTION_H
#define PYTHON_FUNCTION_H

#include <string>
#include <pybind11/pybind11.h>

template <typename Out>
class PythonFunction {
public:
	PythonFunction(const std::string& file, const std::string& fname);
	void set_function(const std::string& file, const std::string& fname);

	template <typename ...Args>
	Out operator()(Args ...args) const;


private:
	pybind11::function func;
};

//-----------------------IMPLEMENTATION---------------------------

template <typename Out>
PythonFunction<Out>::PythonFunction(const std::string& file,
				const std::string& fname) {
	set_function(file, fname);
}

template <typename Out>
void PythonFunction<Out>::set_function(const std::string& file,
				const std::string& fname) {
	func = pybind11::reinterpret_steal<pybind11::function>(
		pybind11::module_::import(file.c_str()).attr(fname.c_str()));
}

template <typename Out>
template <typename ...Args>
Out PythonFunction<Out>::operator()(Args ...args) const {
	pybind11::object ret = func(args...);
	return ret.cast<Out>();
}


#endif // PYTHON_FUNCTION_H
