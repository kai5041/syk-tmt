#pragma once

#include <iostream>
#include <string>
#include <sstream>

#if defined(_WIN32)
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#endif

namespace smt {

  namespace colors {

    namespace fg { // foreground colors
      constexpr const char* BLACK = "\033[30m";
      constexpr const char* RED = "\033[31m";
      constexpr const char* GREEN = "\033[32m";
      constexpr const char* YELLOW = "\033[33m";
      constexpr const char* BLUE = "\033[34m";
      constexpr const char* MAGENTA = "\033[35m";
      constexpr const char* CYAN = "\033[36m";
      constexpr const char* WHITE = "\033[37m";
      constexpr const char* RESET = "\033[39m"; // default foreground
    }

    namespace bg { // background colors
      constexpr const char* BLACK = "\033[40m";
      constexpr const char* RED = "\033[41m";
      constexpr const char* GREEN = "\033[42m";
      constexpr const char* YELLOW = "\033[43m";
      constexpr const char* BLUE = "\033[44m";
      constexpr const char* MAGENTA = "\033[45m";
      constexpr const char* CYAN = "\033[46m";
      constexpr const char* WHITE = "\033[47m";
      constexpr const char* RESET = "\033[49m"; // default background
    }

    constexpr const char* RESET_ALL = "\033[0m"; // reset all attributes
  }

#if defined(_WIN32)
  // Convert UTF-8 string to UTF-16
  inline std::wstring to_wide(const char* utf8) {
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, nullptr, 0);
    std::wstring wstr(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, utf8, -1, &wstr[0], size_needed);
    if (!wstr.empty()) wstr.pop_back(); // remove extra null
    return wstr;
  }

  // Initialize console for UTF-8 output
  inline void init_console_utf8() {
    SetConsoleOutputCP(CP_UTF8);
    _setmode(_fileno(stdout), _O_U16TEXT);
  }
#endif

  // Centralized console buffer
  class Console {
  public:
#if defined(_WIN32)
    std::wostringstream buffer;
#else
    std::ostringstream buffer;
#endif

    // Append text to buffer
    void write(const std::string& str) {
#if defined(_WIN32)
      buffer << to_wide(str.c_str());
#else
      buffer << str;
#endif
    }

    // Append newline
    void newline() {
#if defined(_WIN32)
      buffer << L"\n";
#else
      buffer << "\n";
#endif
    }

    // Flush buffer to console and clear
    void flush() {
#if defined(_WIN32)
      std::wcout << buffer.str();
      std::wcout.flush();
#else
      std::cout << buffer.str();
      std::cout.flush();
#endif
      buffer.str(L"");
      buffer.clear();
    }
  };

  // Global console instance
  inline Console console;

  constexpr const char* MAJOR = "1";
  constexpr const char* MINOR = "0";
  constexpr const char* PATCH = "0";
  inline std::string VERSION = std::string(MAJOR) + "." + MINOR + "." + PATCH;

} // namespace smt
