#pragma once

#include <iostream>
#include <string>
#include <sstream>

#if defined(_WIN32)
#include <windows.h>
#endif

namespace syk_tmt {

  namespace colors {

    namespace fg {
      constexpr const char* BLACK   = "\033[30m";
      constexpr const char* RED     = "\033[31m";
      constexpr const char* GREEN   = "\033[32m";
      constexpr const char* YELLOW  = "\033[33m";
      constexpr const char* BLUE    = "\033[34m";
      constexpr const char* MAGENTA = "\033[35m";
      constexpr const char* CYAN    = "\033[36m";
      constexpr const char* WHITE   = "\033[37m";
      constexpr const char* RESET   = "\033[39m";
    }

    namespace bg {
      constexpr const char* BLACK   = "\033[40m";
      constexpr const char* RED     = "\033[41m";
      constexpr const char* GREEN   = "\033[42m";
      constexpr const char* YELLOW  = "\033[43m";
      constexpr const char* BLUE    = "\033[44m";
      constexpr const char* MAGENTA = "\033[45m";
      constexpr const char* CYAN    = "\033[46m";
      constexpr const char* WHITE   = "\033[47m";
      constexpr const char* RESET   = "\033[49m";
    }

    constexpr const char* RESET_ALL = "\033[0m";
  }

#if defined(_WIN32)
  inline void init_console_utf8() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Enable ANSI escape processing
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
      DWORD mode = 0;
      GetConsoleMode(hOut, &mode);
      SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }
  }
#endif

  class Console {
  public:
    std::ostringstream buffer;

    void write(const std::string& str) {
      buffer << str;
    }

    void newline() {
      buffer << '\n';
    }

    void flush() {
      std::cout << buffer.str();
      std::cout.flush();
      buffer.str("");
      buffer.clear();
    }

    void clear() {
#if defined(_WIN32)
      std::cout << "\033[2J\033[H";
#else
      std::cout << "\033[2J\033[H";
#endif
    }
  };

  inline Console console;

  constexpr const char* MAJOR = "1";
  constexpr const char* MINOR = "0";
  constexpr const char* PATCH = "0";
  inline std::string VERSION = std::string(MAJOR) + "." + MINOR + "." + PATCH;

} // namespace syk_tmt
