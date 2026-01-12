#pragma once

#include <functional>

#include <syk_tmt/ResourceLocator.hpp>
#include <syk_tmt/defs.hpp>

namespace syk_tmt {

class Dispatcher;

struct Command {
  std::string name;
  std::string help;
  std::function<u32(Vec<String> &)> func;
};

class Dispatcher {
private:
  Map<std::string, Command> commands;
  ResourceLocator resource_locator;
  VirtualPathState virtual_path_state;

public:
  Dispatcher();

  u32 execute(String &cmd, Vec<String> &args);

  u32 run();
};

} // namespace syk_tmt
