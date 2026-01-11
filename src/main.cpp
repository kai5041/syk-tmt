#include <smt/helpers.hpp>

#include <smt/Dispatcher.hpp>

using namespace smt;


int main() {
#if defined(_WIN32)
	init_console_utf8();
#endif

	return Dispatcher().run();
}


