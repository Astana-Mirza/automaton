/*
COMPILE ON LINUX WITH:

g++ -O3 -Wall -shared -std=c++2a -fPIC $(python3 -m pybind11 --includes) \
bit_adaptor.cpp -o bit$(python3-config --extension-suffix)

COMPILE ON WINDOWS WITH GOD'S MERCY
*/

#include <bit>
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(bit, m) {
	m.def("rotl64", std::rotl<uint64_t>);
	m.def("rotl32", std::rotl<uint32_t>);
	m.def("rotr64", std::rotr<uint64_t>);
	m.def("rotr32", std::rotr<uint32_t>);
	m.def("countl_zero64", std::countl_zero<uint64_t>);
	m.def("countl_zero32", std::countl_zero<uint32_t>);
	m.def("countl_one64", std::countl_one<uint64_t>);
	m.def("countl_one32", std::countl_one<uint32_t>);
	m.def("countr_zero64", std::countr_zero<uint64_t>);
	m.def("countr_zero32", std::countr_zero<uint32_t>);
	m.def("countr_one64", std::countr_one<uint64_t>);
	m.def("countr_one32", std::countr_one<uint32_t>);
	m.def("popcount64", std::popcount<uint64_t>);
	m.def("popcount32", std::popcount<uint32_t>);

}
