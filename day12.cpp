#include "aoc.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

//???.### 1,1,3

struct Spring {
  std::string record;
  std::vector<int> groups;
};

Spring parseSpring(const std::string &line) {
  const auto sp = aoc::split(line, " ");
  return {sp[0], aoc::intvec(aoc::split(sp[1], ","))};
}

int getUnknown(const std::string& record) {
  return std::accumulate(record.begin(), record.end(), 0, [] (int acc, char c) { return c == '?' ? acc + 1 : acc; });
}

bool match(int num, const Spring &spring) {
  int c = 0;
  bool in_group = false;
  std::vector<int> groups;
  for (char l : spring.record) {
    if(l == '?') {
      l =  (num & 1 << c++) ? '.' : '#';
    }
    if (l == '#') {
      if (in_group) {
        ++groups.back();
      } else {
        groups.push_back(1);
        in_group = true;
      }
    } else {
      in_group = false;
    }
  }
  if (groups.size() == spring.groups.size()) {
    return std::equal(groups.begin(), groups.end(), spring.groups.begin());
  }
  return false;
}

int arrangements(int acc, const Spring& spring) {
  const int unknown = getUnknown(spring.record);
  const uint64_t mutations = 1 << unknown;
//  std::cout << spring.record << " has " << unknown << " unknown and has " << mutations << " mutations.\n";
  for (int i = 0; i != mutations; ++i) { 
    if (match(i, spring)) {
      ++acc;
    }
  }
  return acc;
}

int main() {
  std::vector<Spring> springs;
  aoc::foreach("day12.input", [&springs] (std::string line) {
    springs.push_back(parseSpring(line));
  });
  std::cout << "part 1: " << std::accumulate(springs.begin(), springs.end(), 0, arrangements) << std::endl;
  std::cout << "part 2: " << "" << std::endl;
  return 0;
}

// part 1: 
// part 2: 