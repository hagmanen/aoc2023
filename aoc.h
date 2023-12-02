#include <functional>
#include <string>
#include <vector>

namespace aoc {
  void foreach(const std::string& filename, std::function<void(std::string line)> &&fun);

  std::vector<std::string> split(const std::string& line, const std::string& delimiter);
}
