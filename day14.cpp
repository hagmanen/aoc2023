#include "aoc.h"
#include <iostream>
#include <vector>
#include <numeric>
// Function to rotate the matrix 90 degree clockwise
std::vector<std::string> rotate90Clockwise(const std::vector<std::string> &grid) {
  std::vector<std::string> res(grid);
  const int N = grid.size();
    // Traverse each cycle
  for (int i = 0; i < N / 2; i++) {
    for (int j = i; j < N - i - 1; j++) {
      auto temp = res[i][j];
      res[i][j] = res[N - 1 - j][i];
      res[N - 1 - j][i] = res[N - 1 - i][N - 1 - j];
      res[N - 1 - i][N - 1 - j] = res[j][N - 1 - i];
      res[j][N - 1 - i] = temp;
    }
  }
  return res;
}

std::string tiltLine(const std::string& line) {
  int stones = 0;
  int steps = 0;
  std::string res;
  for ( ; steps != line.length() && line[steps] != '#'; ++steps) {
    if (line[steps] == 'O') {
      ++stones;
    }
  }
  res.append(stones, 'O');
  res.append(steps-stones, '.');
  if (steps == line.length()) {
    return res;
  }
  res += "#";
  ++steps;
  std::string rest = line.substr(steps, line.length() - steps);
  return res + tiltLine(rest);
}

std::vector<std::string> tilt(const std::vector<std::string>& grid) {
  std::vector<std::string> res;
  for (int i = 0; i != grid.size(); ++i) {
    res.emplace_back(tiltLine(grid[i]));
  }
  return res;
}

int accLoad(int acc, const std::string& line) {
  size_t res = 0;
  const size_t len = line.length();
  for (size_t i = 0; i != len; ++i) {
    if (line[i] == 'O') {
      res += len - i;
    }
  }
  return acc + res;
}

int calcLoad(std::vector<std::string> &grid) {
  return std::accumulate(grid.begin(), grid.end(), 0, accLoad);
}

int calcConfig(std::vector<std::string> &grid) {
  const int len = grid.size();
  int config = 0;
  for (int i = 0; i != len; ++i) {
    for (int j = 0; j != len; ++j) {
      if (grid[i][j] == 'O') {
        config += (i * len) + j;
      }
    }
  }
  return config;
}

int round(std::vector<std::string> &grid) {
  grid = tilt(grid);
  grid = rotate90Clockwise(grid);
  grid = tilt(grid);
  grid = rotate90Clockwise(grid);
  grid = tilt(grid);
  grid = rotate90Clockwise(grid);
  grid = tilt(grid);
  grid = rotate90Clockwise(grid);
  const auto load = calcLoad(grid);
  return load;
}

int main() {
  std::vector<std::string> grid;
  aoc::foreach("day14.input", [&grid] (std::string line) {
    grid.push_back(line);
  });
  auto grid1 = rotate90Clockwise(rotate90Clockwise(rotate90Clockwise(grid)));
  grid1 = tilt(grid1);
  std::cout << "part 1: " << calcLoad(grid1) << std::endl;
  auto grid2 = rotate90Clockwise(rotate90Clockwise(rotate90Clockwise(grid)));
  std::vector<int> unique_config;
  std::vector<int> loads;
  uint64_t i = 1000000000;
  int mload = 0;
  for (; i != 0; --i) {
    const auto load = round(grid2);
    auto config = calcConfig(grid2);
    const auto it = std::find(unique_config.begin(), unique_config.end(), config);
    if ( it != unique_config.end()) {
      i %= std::distance(it, unique_config.end());
      mload = load;
      break;
    }
    unique_config.push_back(config);
    loads.push_back(load);
  }
  for (; i != 1; --i) {
    mload = round(grid2);
  }
  std::cout << "part 2: " << mload << std::endl;
  return 0;
}

// part 1: 111339
// part 2: 93736
