#include "aoc.h"
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <numeric>

std::vector<uint64_t> parseSeeds(const std::string& line) {
  return aoc::int64vec(aoc::split(aoc::split(line, ": ")[1], " "));
}

struct RangeMap {
  uint64_t dest;
  uint64_t src;
  uint64_t range;
};

struct Range {
  uint64_t start;
  uint64_t end;
  bool overlap(const Range& r) const {
    return !(end <= r.start || r.end <=  start);
  }
  bool overlap(const RangeMap& r) const {
    return !(end <= r.src || r.src + r.range <=  start);
  }
  bool has_before(const RangeMap& r) const {return start < r.src;}
  bool has_after(const RangeMap& r) const {return end > r.src + r.range;}
  Range before(const RangeMap &r) const {return Range{start, r.src};}
  Range after(const RangeMap &r) const {return Range{r.src + r.range, end};}
  Range mapped(const RangeMap &r) const {return Range{std::max(start, r.src) - r.src + r.dest, std::min(end, r.src + r.range) - r.src + r.dest};}
  void merge(const Range& r) {
    start = std::min(start, r.start);
    end = std::max(end, r.end);
  }
};

struct Ranges {
  std::vector<Range> ranges;
  void add(Range range) {
    const auto rit = std::remove_if(ranges.begin(), ranges.end(), [&range] (const auto &r) {return r.overlap(range);});
    for (auto it = rit; it != ranges.end(); ++it) {
      range.merge(*it);
    }
    ranges.erase(rit, ranges.end());
    ranges.push_back(range);
  }
  void print() const {
    for (const auto& r : ranges) {
      std::cout << r.start << " - " << r.end << std::endl;
    }
    std::cout << "---\n";
  }
};

struct Map {
  std::vector<RangeMap> range_maps;

  uint64_t toDest(uint64_t s) const {
    for (const auto& r : range_maps) {
      if (s >= r.src && s <= r.src + r.range) {
        return s - r.src + r.dest;
      }
    }
    return s;
  }

  Ranges toDest(Ranges ranges) const {
    Ranges result;
    for (const auto& rm : range_maps) {
      Ranges left;
      for (const auto& r : ranges.ranges) {
        if(r.overlap(rm)) {
          if(r.has_before(rm)) {
            left.add(r.before(rm));
          }
          if(r.has_after(rm)) {
            left.add(r.after(rm));
          }
          result.add(r.mapped(rm));
        } else {
          left.add(r);
        }
      }
      ranges.ranges = left.ranges;
    }
    for(const auto& r: ranges.ranges) {
      result.add(r);
    }
    return result;
  }
};

void addToMap(Map &map, const std::string &line) {
  if (line.empty()) {
    return;
  }
  const auto numbers = aoc::split(line, " ");
  uint64_t dest = std::stoll(numbers[0]);
  uint64_t src = std::stoll(numbers[1]);
  uint64_t rng = std::stoll(numbers[2]);
  map.range_maps.push_back({dest, src, rng});
}

uint64_t seedToLocation(uint64_t seed, const std::vector<Map>& maps) {
  for (const auto &m : maps) {
    seed = m.toDest(seed);
  }
  return seed;
}

Ranges seedsToRanges(const std::vector<uint64_t>& seeds) {
  Ranges res;
  for (int i = 0; i < seeds.size(); i+=2) {
    res.add(Range{seeds[i], seeds[i] + seeds[i+1]});
  }
  return res;
}

int main() {
  std::vector<Map> maps;
  std::vector<uint64_t> seeds;

  aoc::foreach("day5.input", [&maps, &seeds] (std::string line) {
    if (seeds.empty()) {
      seeds = parseSeeds(line);
    } else if(!line.empty() && *line.rbegin() == ':') {
      maps.push_back(Map());
    } else {
      addToMap(*maps.rbegin(), line);
    }
  });
  std::vector<uint64_t> locations;
  std::transform(seeds.begin(),
                 seeds.end(),
                 std::back_inserter(locations),
                 [&maps] (uint64_t seed) {return seedToLocation(seed, maps);});
  const uint64_t min_location = *std::min_element(locations.begin(), locations.end());
  auto ranges = seedsToRanges(seeds);
  for (const auto &map : maps) {
    ranges = map.toDest(ranges);
  }
  auto min2 = ranges.ranges.at(0).start;
  for (const auto r : ranges.ranges) {
    min2 = std::min(min2, r.start);
  }
  std::cout << "part 1: " << min_location << std::endl;
  std::cout << "part 2: " << min2 << std::endl;
  return 0;
}

// part 1: 177942185
// part 2: 69841803
