#include <functional>
#include <string>
#include <vector>
#include <set>

namespace aoc {
  void foreach(const std::string& filename, std::function<void(std::string line)> &&fun);

  std::vector<std::string> split(const std::string& line, const std::string& delimiter);

  std::set<int> intset(std::vector<std::string> &&numbers);
  std::vector<int> intvec(std::vector<std::string> &&numbers);
  std::set<uint64_t> int64set(std::vector<std::string> &&numbers);
  std::vector<uint64_t> int64vec(std::vector<std::string> &&numbers);
}
