#include "../include/mainwindow.h"
/*#include <iostream>
#include <cstdint>
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include "../inc/automatons/crypto_automaton.h"

namespace py = pybind11;

int main() {
	uint32_t init = 0;
	py::scoped_interpreter guard{};
	py::module_ calc = py::module_::import("func");
	auto automaton = make_crypto<uint32_t, std::vector<uint32_t>>(init, init,
		[](uint32_t x, uint32_t q, uint32_t key) { return q+1; },
		[calc](uint32_t x, uint32_t q, uint32_t key) {
			return calc.attr("output")(x, q).cast<std::vector<uint32_t>>();
		}
	);
	auto v = automaton.step(228);
	std::cout << "First step: " << v[0] << " " << v[1] << '\n';
	return 0;
}*/


#include <QApplication>

int main( int argc, char *argv[] )
{
     QApplication a( argc, argv );
     MainWindow w;
     w.show();
     return a.exec();
}
