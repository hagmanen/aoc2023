#include "aoc.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>

int waysToBeat(uint64_t time, uint64_t distance) {
  int ways = 0;
  for (uint64_t i = 1; i != time; ++i) {
    if (distance / i < time - i) {++ways;}
  }
  return ways;
}

int main() {
  std::vector<std::vector<uint64_t>> input;
  std::vector<uint64_t> input2;
  aoc::foreach("day6.input", [&input, &input2] (std::string line) {
    input.emplace_back(aoc::int64vec(aoc::split(aoc::split(line, ": ")[1], " ")));
    line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
    input2.emplace_back(std::stoll(aoc::split(line, ":")[1]));
  });
  int res = 1;
  for (size_t i = 0; i != input[0].size(); ++i) {
    res *= waysToBeat(input[0][i], input[1][i]);
  }
  std::cout << "part 1: " << res << std::endl;
  std::cout << "part 2: " << waysToBeat(input2[0], input2[1]) << std::endl;
  return 0;
}

// part 1: 2756160
// part 2: 34788142
