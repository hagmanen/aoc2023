#include "aoc.h"
#include <iostream>
#include <algorithm>
#include <numeric>


int next(const std::vector<int> &row) {
  if (row.size() == 1) {
    return 0;
  }
  bool done = true;
  auto it = row.begin();
  int prev = *it++;
  std::vector<int> next_row;
  next_row.reserve(row.size()-1);
  for (; it != row.end(); ++it) {
    next_row.push_back(*it - prev);
    prev = *it;
    done &= prev == 0;
  }
  if (done) {
    return 0;
  }
  return *row.rbegin() + next(next_row);
}

int nextsum(int acc, const std::vector<int> &row) {
  return acc + next(row);
}

int pre(const std::vector<int> &row) {
  if (row.size() == 1) {
    return 0;
  }
  bool done = true;
  auto it = row.begin();
  int prev = *it++;
  std::vector<int> next_row;
  next_row.reserve(row.size()-1);
  for (; it != row.end(); ++it) {
    next_row.push_back(*it - prev);
    prev = *it;
    done &= prev == 0;
  }
  if (done) {
    return 0;
  }
  return *row.begin() - pre(next_row);
}

int presum(int acc, const std::vector<int> &row) {
  return acc + pre(row);
}

int main() {
  std::vector<std::vector<int>> input;
  aoc::foreach("day9.input", [&input] (std::string line) {
    input.emplace_back(aoc::intvec(aoc::split(line, " ")));
  });
  std::cout << "part 1: " << std::accumulate(input.begin(), input.end(), 0, nextsum) << std::endl;
  std::cout << "part 2: " << std::accumulate(input.begin(), input.end(), 0, presum) << std::endl;
  return 0;
}

// part 1: 1743490457
// part 2: 1053