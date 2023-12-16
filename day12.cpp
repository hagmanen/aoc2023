#include "aoc.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>

//???.### 1,1,3
struct Spring {
  std::string record;
  std::vector<int> groups;
};

Spring parseSpring(const std::string &line) {
  const auto sp = aoc::split(line, " ");
  return {sp[0], aoc::intvec(aoc::split(sp[1], ","))};
}

struct State {
  int x;
  int y;
  int z;
};

bool operator<(const State& lhs, const State& rhs) {
    return std::tie(lhs.x, lhs.y, lhs.z) < std::tie(rhs.x, rhs.y, rhs.z);
}

bool match(char c1, char c2) {
  return c1 == '?' || c1 == c2;
}

uint64_t arrangements(const Spring& spring, int pos, int left_in_group, int next_group, std::map<State, uint64_t> &cache) {
  if (pos == spring.record.length()) {
    if (left_in_group <= 0 && next_group == spring.groups.size()) {
      return 1;
    }
    return 0;
  }
  const auto it = cache.find({pos, left_in_group, next_group});
  if (it != cache.end()) {
    return it->second;
  }

  uint64_t count = 0;
  if (left_in_group <= 0 && match(spring.record[pos], '.')) {
    count += arrangements(spring, pos + 1, -1, next_group, cache);
  }
  if (match(spring.record[pos], '#')) {
    if (left_in_group > 0) {
        count += arrangements(spring, pos + 1, left_in_group - 1, next_group, cache);
    } else if (left_in_group < 0 && next_group < spring.groups.size()) {
        count += arrangements(spring, pos + 1, spring.groups[next_group] - 1, next_group + 1, cache);
    }
  }

  cache.insert({{pos, left_in_group, next_group}, count});
  return count;
}

uint64_t sumArrangements(uint64_t acc, const Spring& spring) {
  std::map<State, uint64_t> cache;
  return acc + arrangements(spring, 0, -1, 0, cache);
}

std::vector<int> five(const std::vector<int>& v) {
  std::vector<int> r;
  for (int i = 0; i != 5; ++i) {
    r.insert(r.end(), v.begin(), v.end());
  }
  return r;
}

std::string five(const std::string& p) {
  std::string r;
  for (int i = 0; i != 5; ++i) {
    r += p;
    if (i != 4) {
      r += "?";
    }
  }
  return r;
}

Spring part2spring(const Spring &s) {
  std::string record = five(s.record);
  std::vector<int> groups = five(s.groups);
  return {record, groups};
}

std::vector<Spring> part2springs(const std::vector<Spring> &springs) {
  std::vector<Spring> s2;
  for(const auto &spring: springs) {
    s2.push_back(part2spring(spring));
  }
  return s2;
}

int main() {
  std::vector<Spring> springs;
  aoc::foreach("day12.input", [&springs] (std::string line) {
    springs.push_back(parseSpring(line));
  });
  std::cout << "part 1: " << std::accumulate(springs.begin(), springs.end(), (uint64_t)0, sumArrangements) << std::endl;
  const auto springs2 = part2springs(springs);
  std::cout << "part 2: " << std::accumulate(springs2.begin(), springs2.end(), (uint64_t)0, sumArrangements) << std::endl;
  return 0;
}

// part 1: 7163
// part 2: 17788038834112