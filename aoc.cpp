#include "aoc.h"

#include <fstream>

namespace aoc {
void foreach(const std::string& filename, std::function<void(std::string line)> &&fun) {
  std::ifstream input;
  input.open(filename);
  std::string line;
  while (std::getline(input, line)) {
    fun(line);
  }
  input.close();
}

std::vector<std::string> split(const std::string& line, const std::string& delimiter) {
  size_t start = 0, end;
  std::vector<std::string> result;
  while((end = line.find(delimiter, start)) != std::string::npos) {
    result.emplace_back(line.substr(start, end - start));
    start = end + delimiter.size();
  }
  result.emplace_back(line.substr(start, line.size() - start));
  return result;
}
}