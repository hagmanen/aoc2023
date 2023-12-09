#include "aoc.h"

#include <fstream>
#include <algorithm>

namespace aoc {
void foreach(const std::string& filename, std::function<void(std::string line)> &&fun) {
  std::ifstream input;
  input.open("../"+filename);
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
    if (start != end) {
      result.emplace_back(line.substr(start, end - start));
    }
    start = end + delimiter.size();
  }
  result.emplace_back(line.substr(start, line.size() - start));
  return result;
}

std::set<int> intset(std::vector<std::string> &&numbers) {
  std::set<int> result;
  std::transform(numbers.begin(),
                 numbers.end(),
                 std::inserter(result, result.begin()),
                 [] (const std::string& str){ return std::stoi(str);});
  return result;
}

std::vector<int> intvec(std::vector<std::string> &&numbers) {
  std::vector<int> result;
  std::transform(numbers.begin(),
                 numbers.end(),
                 std::back_inserter(result),
                 [] (const std::string& str){ return std::stoi(str);});
  return result;
}

std::set<uint64_t> int64set(std::vector<std::string> &&numbers) {
  std::set<uint64_t> result;
  std::transform(numbers.begin(),
                 numbers.end(),
                 std::inserter(result, result.begin()),
                 [] (const std::string& str){ return std::stoll(str);});
  return result;
}

std::vector<uint64_t> int64vec(std::vector<std::string> &&numbers) {
  std::vector<uint64_t> result;
  std::transform(numbers.begin(),
                 numbers.end(),
                 std::back_inserter(result),
                 [] (const std::string& str){ return std::stoll(str);});
  return result;
}
}