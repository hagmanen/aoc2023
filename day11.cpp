#include "aoc.h"
#include <iostream>
#include <set>
#include <cmath>

using Coord = std::pair<int64_t, int64_t>;

std::set<Coord> adjustCols(std::set<Coord> stars, const std::set<int64_t> &pop_cols, int64_t gap) {
  int64_t mx = *pop_cols.rbegin();
  std::set<int64_t> empty;
  for (int64_t c = 0; c != mx; ++c) {
    if (pop_cols.find(c) == pop_cols.end()) {
      empty.insert(c);
    }
  }

  int64_t offset = 0;
  for(int64_t c : empty) {
    std::set<Coord> mut;
    for (auto &star : stars) {
      if (star.first > c + offset) {
        mut.insert({star.first + gap, star.second});
      } else {
        mut.insert(star);
      }
    }
    std::swap(stars, mut);
    offset += gap;
  }
  return stars;
}

int64_t dist(const Coord& a, const Coord& b) {
  return std::abs(a.first - b.first) + std::abs(a.second - b.second);
}

int64_t sumDist(const Coord& star, const std::set<Coord>::iterator& first, const std::set<Coord>::iterator& last) {
  if (first == last) {
    return 0;
  }
  int64_t sum = 0;
  for (auto it = first; it != last; ++it) {
    sum += dist(star, *it);
  }
  return sum + sumDist(*first, std::next(first), last);
}

int64_t solve(int exp) {
  std::set<int64_t>  pop_cols;
  std::set<Coord> stars;
  int64_t y = 0;
  aoc::foreach("day11.input", [&pop_cols, &stars, &y, exp] (std::string line) {
    bool empty = true;
    for(int64_t x = 0; x != line.length(); ++x) {
      if (line[x] == '#') {
        pop_cols.insert(x);
        stars.insert({x, y});
        empty = false;
      }
    }
    y += empty ? exp : 1;
  });
  std::set<Coord> stars1 = adjustCols(stars, pop_cols, exp - 1);
  return sumDist(*stars1.begin(), std::next(stars1.begin()), stars1.end());
}

int main() {
  std::cout << "part 1: " << solve(2) << std::endl;
  std::cout << "part 2: " << solve(1000000) << std::endl;
  return 0;
}

// part 1: 10494813
// part 2: 840988812853