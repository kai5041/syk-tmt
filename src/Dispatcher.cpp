#include <iostream>

#include <smt/Dispatcher.hpp>
#include <smt/helpers.hpp>

namespace smt {

  Dispatcher::Dispatcher() {

    commands["exit"] = {
        "exit",
        "exit",
        [](Vec<String>& args)->u32 {
          u32 status_code = 0;

          if (args.size() > 1) status_code = std::stoull(args[1]);
           else status_code = 0;

           return status_code;
         }
    };

    commands["version"] = {
        "version",
        "version",
        [](Vec<String>&)->u32 {
          console.write("所有権端末 / Shoyuuken Tanmatsu (SYK-TMT)\nVersion: " + smt::VERSION + "\nRespository: https://github.com/kai5041/syk-tmt");
          console.newline();
          console.flush();
          return 0;
         }
    };

    commands["sys"] = {
        "sys",
        "sys",
        [](Vec<String>& args)->u32 {
          args.erase(args.begin());
          String cmd = "";

          for (auto& arg : args)
            cmd += arg + " ";

          return std::system(cmd.c_str());
         }
    };

    commands["cls"] = {
        "cls",
        "cls",
        [](Vec<String>&)->u32 {
          console.clear();
          return 0;
         }
    };



    //
  }

  u32 Dispatcher::execute(String& cmd, Vec<String>& args) {
    u32 status_code = 0;

    auto it = this->commands.find(cmd);

    if (it == commands.end()) {
      console.write(std::string("[") + colors::fg::RED + "ERROR" + colors::fg::RESET + "] Command '" + cmd + "' not found");
      console.newline();
      console.flush();
      return -1;
    }

    status_code = it->second.func(args);

    return status_code;
  }

  u32 Dispatcher::run() {
    String line;
    String cmd;
    u32 status_code = 0;
    Vec<String> args;

    do {
      line.clear();
      cmd.clear();
      args.clear();

      if (status_code == 0) {
        console.write(colors::fg::GREEN);
        console.write("V");
      }
      else {
        console.write(colors::fg::RED);
        console.write("X");
      }

      console.write(colors::fg::RESET);
      console.write(" > ");
      console.flush();


      std::getline(std::cin, line);
      if (line.empty()) continue;

      std::stringstream ss(line);
      String token;
      while (ss >> token) args.push_back(token);

      if (args.empty()) continue;

      cmd = args[0];
      status_code = this->execute(cmd, args);

    } while (cmd != "exit");

    return status_code;
  }


} // namespace smt
