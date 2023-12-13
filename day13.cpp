#include "aoc.h"
#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>

std::vector<std::string> rotate(const std::vector<std::string>& grid) {
  int len = grid.front().length();
  std::vector<std::string> res(len, std::string(""));
  for (int c = 0 ; c != grid.size(); ++c) {
    for(int r = 0; r != len; ++r) {
      res[r] += grid[c][r];
    }
  }
  return res;
}

bool reflection(const std::vector<std::string>& grid, int line, int tol) {
  std::vector<std::string> lo(grid.begin(), grid.begin() + line);
  std::vector<std::string> hi(grid.begin() + line, grid.end());
  auto len = std::min(lo.size(), hi.size());
  std::reverse(lo.begin(), lo.end());
  lo.resize(len);
  hi.resize(len);
  int smudge = 0;
  for (int i = 0; i != len; ++i) {
    for (int j = 0; j != lo[i].length(); ++j) {
      if (lo[i][j] != hi[i][j]) {
        ++smudge;
      }
    }
  }
  return smudge == tol;
}

int reflectRow(const std::vector<std::string>& grid, int tol) {
  for (int i = 1; i < grid.size(); ++i) {
    if (reflection(grid, i, tol)) {
      return i;
    }
  }
  return 0;
}

int score(const std::vector<std::string>& grid, int tol) {
  if (int row = reflectRow(grid, tol)) {
    return 100 *row;
  }
  return reflectRow(rotate(grid), tol);
}

int score1(int acc, const std::vector<std::string>& grid) {
  return acc + score(grid, 0);
}

int score2(int acc, const std::vector<std::string>& grid) {
  return acc + score(grid, 1);
}

int main() {
  std::vector<std::vector<std::string>> grids = {std::vector<std::string>()};
  aoc::foreach("day13.input", [&grids] (std::string line) {
    if(line.empty()) {
      grids.emplace_back(std::vector<std::string>());
    } else {
      grids.back().push_back(line);
    }
  });

  std::cout << "part 1: " << std::accumulate(grids.begin(), grids.end(), 0, score1) << std::endl;
  std::cout << "part 2: " << std::accumulate(grids.begin(), grids.end(), 0, score2) << std::endl;
  return 0;
}

// part 1: 30158
// part 2: 36474
