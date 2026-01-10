#include <unordered_map>
#include <functional>

#include <smt/cli.hpp>
#include <smt/defs.hpp>

using namespace smt;

Map<String, std::function<u32(Vec<String>&)>> commands;

// Macro to define and auto-register functions
#define SMT_FUNC(name) \
    u32 name(Vec<String> &args); \
    struct name##_registrar { \
        name##_registrar() { commands[#name] = name; } \
    } name##_instance; \
    u32 name(Vec<String> &args)

SMT_FUNC(version) {
	console.write(
		"所有権端末 / Shoyuuken Tanmatsu (SYK-TMT) version " + std::string(smt::VERSION) + "\n"
		"Repository: https://github.com/kai5041/syk-tmt\n" +
		std::string(smt::colors::bg::WHITE) +
		smt::colors::fg::BLACK +
		" HARMONY連 " +
		smt::colors::RESET_ALL + " For innovation."
		"\n"
	);

	console.flush();

	return 0;
}



int main() {
#if defined(_WIN32)
	init_console_utf8();
#endif

	u32 status_code = 0;
	String line;

	while (true) {
		console.write("> ");
		console.flush();

		std::getline(std::cin, line);

		std::istringstream iss(line);
		Vec<String> args;
		String cmd;

		if (!(iss >> cmd)) {
			continue;
		}

		String arg;
		while (iss >> arg) {
			args.push_back(arg);
		}

		if (cmd == "exit") {
			status_code = 0;
			break;
		}

		auto it = commands.find(cmd);
		if (it == commands.end()) {
			console.write("[" + std::string(smt::colors::fg::RED) + "ERROR" + smt::colors::fg::RESET + "] Command does not exist\n");
			continue;
		}

		status_code = it->second(args);
	}

	return status_code;
}
