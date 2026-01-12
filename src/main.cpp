#include <syk_tmt/helpers.hpp>

#include <syk_tmt//Dispatcher.hpp>

using namespace syk_tmt;


int main() {
#if defined(_WIN32)
	init_console_utf8();
#endif

	return Dispatcher().run();
}


