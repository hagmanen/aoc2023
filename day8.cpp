#include "aoc.h"
#include <iostream>
#include <map>
#include <string>
#include <numeric>

int solve1(const std::string &inst, const std::map<std::string, std::pair<std::string, std::string>>& tree) {
  int steps = 0;
  std::string pos = "AAA";
  while(true) {
    for(const auto& c : inst) {
      pos = c == 'L' ? tree.at(pos).first : tree.at(pos).second;
      ++steps;
      if (pos == "ZZZ") {
        return steps;
      }
    }
  }
}

uint64_t sol(const std::string &inst, const std::map<std::string, std::pair<std::string, std::string>>& tree, std::string pos) {
  uint64_t steps = 0;
  while(true) {
    for(const auto& c : inst) {
      pos = c == 'L' ? tree.at(pos).first : tree.at(pos).second;
      ++steps;
      if (pos.find('Z') != std::string::npos) {
        return steps;
      }
    }
  }
}

uint64_t solve2(const std::string &inst, const std::map<std::string, std::pair<std::string, std::string>>& tree) {
  std::vector<std::string> pos;
  for (const auto &n : tree) {
    if(n.first.find('A') != std::string::npos) {
      pos.push_back(n.first);
    }
  }
  uint64_t steps = sol(inst, tree, "AAA");
  for (const auto &p : pos) {
    steps = std::lcm(steps, sol(inst, tree, p));
  }
  return steps;
}

int main() {
  std::string inst;
  std::map<std::string, std::pair<std::string, std::string>> tree;
  aoc::foreach("day8.input", [&inst, &tree] (std::string line) {
    if (inst.empty()) {
      inst = line;
    } else if(!line.empty()) {
      tree[line.substr(0, 3)] = {line.substr(7, 3), line.substr(12, 3)};
    }
  });
  std::cout << "part 1: " << solve1(inst, tree) << std::endl;
  std::cout << "part 2: " << solve2(inst, tree) << std::endl;
  return 0;
}

// part 1: 17263
// part 2: 14631604759649