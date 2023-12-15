#include "aoc.h"
#include <iostream>

int hashcode(const std::string& code) {
  int h = 0;
  for(auto c : code) {
    h += (int) c;
    h *= 17;
    h %= 256;
  }
  return h;
}

int hash(const std::string& code) {
  int h = 0;
  for (const auto& com : aoc::split(code, ",")) {
    h += hashcode(com);
  }
  return h;
}

using Lens = std::pair<std::string, int>;
using Lenses = std::vector<std::pair<std::string, int>>;

void remove(Lenses& lenses, const std::string lens) {
  lenses.erase(std::remove_if(lenses.begin(), 
                              lenses.end(),
                              [&lens](const Lens& l) { return l.first == lens; }),
               lenses.end());
}

void modify(Lenses& lenses, const std::string lens, int focal) {
  for (auto & l : lenses) {
    if (l.first == lens) {
      l.second = focal;
      return;
    }
  }
  lenses.push_back({lens, focal});
}

int sumLenses(const Lenses& lenses) {
  int r = 0;
  for (int i = 0; i != lenses.size(); ++i) {
    r += (i + 1) * lenses[i].second;
  }
  return r;
}

int sum(const std::vector<Lenses>& map) {
  int r = 0;
  for (int i = 0; i != map.size(); ++i) {
    r += (i + 1) * sumLenses(map[i]);
  }
  return r;
}

int hashmap(const std::string& code) {
  std::vector<Lenses> map(256, Lenses());
  for (const auto& com : aoc::split(code, ",")) {
    if (com.back() == '-') {
      const auto lens = com.substr(0, com.length() - 1);
      int h = hashcode(lens);
      remove(map[h], lens);
    } else {
      const auto lens = aoc::split(com, "=");
      int h = hashcode(lens[0]);
      modify(map[h], lens[0], std::stoi(lens[1]));
    }
  }
  return sum(map);
}

int main() {
  std::string code;
  aoc::foreach("day15.input", [&code] (std::string line) {
    code += line;
  });
  std::cout << "part 1: " << hash(code) << std::endl;
  std::cout << "part 2: " << hashmap(code) << std::endl;
  return 0;
}

// part 1: 511416
// part 2: 290779