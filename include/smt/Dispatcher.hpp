#pragma once

#include <functional>

#include <smt/defs.hpp>

namespace smt {

  class Dispatcher;

  struct Command {
    std::string name;
    std::string help;
    std::function<u32(Vec<String> &)> func;
  };

  class Dispatcher {
  private:
    Map<std::string, Command> commands;

  public:
    Dispatcher();

    u32 execute(String &cmd, Vec<String> &args);

    u32 run();

  };

} // namespace xwm
