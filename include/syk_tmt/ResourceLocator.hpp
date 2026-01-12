#pragma once

#include <cstdlib>
#include <filesystem>
#include <stdexcept>

namespace syk_tmt {

namespace fs = std::filesystem;

class ResourceLocator {
public:
  static const fs::path &root_dir() {
    static const fs::path dir = [] {
#ifdef _WIN32
      const char *home = std::getenv("USERPROFILE");
#else
      const char *home = std::getenv("HOME");
#endif
      if (!home) {
        throw std::runtime_error("Home (~) directory not found");
      }
      return fs::path(home) / ".syk-tmt";
    }();
    return dir;
  }

  static fs::path convert_to_real_path(const fs::path &virtual_path) {
    if (virtual_path.is_absolute()) {
      return virtual_path;
    }
    return root_dir() / virtual_path;
  }

  static fs::path convert_to_virtual_path(const fs::path &real_path) {
    fs::path root = root_dir();
    fs::path canonical_root = fs::weakly_canonical(root);
    fs::path canonical_real = fs::weakly_canonical(real_path);

    auto mismatch_pair =
        std::mismatch(canonical_root.begin(), canonical_root.end(),
                      canonical_real.begin(), canonical_real.end());

    if (mismatch_pair.first != canonical_root.end()) {
      throw std::runtime_error("Path is outside virtual root");
    }

    fs::path relative;
    for (auto it = mismatch_pair.second; it != canonical_real.end(); ++it) {
      relative /= *it;
    }
    return relative;
  }
};

class VirtualPathState {
private:
  fs::path current_virtual_path{"."};

public:
  const fs::path& cwd() const {
    return current_virtual_path;
  }

  void set_cwd(const fs::path& new_path) {
    current_virtual_path = fs::weakly_canonical(new_path);
  }

  fs::path resolve(const fs::path& p) const {
    if (p.is_absolute()) {
      return p;
    }
    return current_virtual_path / p;
  }
};

} // namespace syk_tmt
