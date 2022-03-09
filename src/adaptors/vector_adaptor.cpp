/*
COMPILE ON LINUX WITH:

g++ -O3 -Wall -shared -std=c++2a -fPIC $(python3 -m pybind11 --includes) \
vector_adaptor.cpp -o vector$(python3-config --extension-suffix)

COMPILE ON WINDOWS WITH GOD'S MERCY
*/

#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>

namespace py = pybind11;

PYBIND11_MAKE_OPAQUE(std::vector<bool>);
PYBIND11_MAKE_OPAQUE(std::vector<uint32_t>);
PYBIND11_MAKE_OPAQUE(std::vector<uint64_t>);

PYBIND11_MODULE(vector, m) {
	py::bind_vector<std::vector<bool>>(m, "VectorBool");
	py::bind_vector<std::vector<uint32_t>>(m, "VectorU32");
	py::bind_vector<std::vector<uint64_t>>(m, "VectorU64");
}
