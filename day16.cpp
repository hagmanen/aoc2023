#include "aoc.h"
#include <iostream>
#include <numeric>
#include <cstdlib>

enum class Dir {
  North, East, South, West
};

struct Beam {
  int x;
  int y;
  Dir dir;
};

bool operator<(const Beam& lhs, const Beam& rhs) {
    return std::tie(lhs.x, lhs.y, lhs.dir) < std::tie(rhs.x, rhs.y, rhs.dir);
}

Beam forward(const Beam &beam) {
  switch (beam.dir)
  {
  case Dir::North:
    return {beam.x, beam.y - 1, beam.dir};
  case Dir::East:
    return {beam.x + 1, beam.y, beam.dir};
  case Dir::South:
    return {beam.x, beam.y + 1, beam.dir};
  case Dir::West:
    return {beam.x - 1, beam.y, beam.dir};
  default:
    std::abort();
  }
}

Beam split(const Beam &beam, std::vector<Beam> &beams) {
  switch (beam.dir)
  {
  case Dir::North:
  case Dir::South:
    beams.push_back({beam.x + 1, beam.y, Dir::East});
    return {beam.x - 1, beam.y, Dir::West};
  case Dir::East:
  case Dir::West:
    beams.push_back({beam.x, beam.y - 1, Dir::North});
    return {beam.x, beam.y + 1, Dir::South};
  default:
    std::abort();
  }
}

// for /
Beam turn(const Beam& beam) {
  switch (beam.dir)
  {
  case Dir::North:
    return {beam.x + 1, beam.y, Dir::East};
  case Dir::East:
    return {beam.x, beam.y - 1, Dir::North};
  case Dir::South:
    return {beam.x - 1, beam.y, Dir::West};
  case Dir::West:
    return {beam.x, beam.y + 1, Dir::South};
  default:
    std::abort();
  }
}
// for \b   
Beam turnback(const Beam& beam) {
  switch (beam.dir)
  {
  case Dir::North:
    return {beam.x - 1, beam.y, Dir::West};
  case Dir::East:
    return {beam.x, beam.y + 1, Dir::South};
  case Dir::South:
    return {beam.x + 1, beam.y, Dir::East};
  case Dir::West:
    return {beam.x, beam.y - 1, Dir::North};
  default:
    std::abort();
  }
}
Beam step(const Beam& beam, char encounter, std::vector<Beam> &beams) {
  switch(encounter) {
    case '.':
      return forward(beam);
    case '|':
      if (beam.dir == Dir::East || beam.dir == Dir::West) {
        return split(beam, beams);
      }
      return forward(beam);
    case '-':
      if (beam.dir == Dir::North || beam.dir == Dir::South) {
        return split(beam, beams);
      }
      return forward(beam);
    case '\\':
      return turnback(beam);
    case '/':
      return turn(beam);
    default:
    std::abort();
  }
}

void energize(const Beam& beam, std::vector<Beam> &beams, const std::vector<std::string> &grid, std::set<Beam> &done) {
  if (beam.x < 0 || beam.x >= grid.front().length() || beam.y < 0 || beam.y >= grid.size()) {
    return;
  }
  if (done.find(beam) != done.end()) {
    return;
  }
  done.insert(beam);
  auto new_beam = step(beam, grid[beam.y][beam.x], beams);
  return energize(new_beam, beams, grid, done);
}

int unique(const std::set<Beam> &done) {
  std::set<std::pair<int, int>> lit;
  std::accumulate(done.begin(), done.end(), 0, [&lit] (int, const Beam& beam){lit.insert({beam.x, beam.y}); return 0;});
  return lit.size();
}

int energized(const Beam& origin_beam, const std::vector<std::string> &grid) {
  std::set<Beam> done;
  std::vector<Beam> beams = {origin_beam};
  while(!beams.empty()) {
    const auto beam = beams.back();
    beams.pop_back();
    energize(beam, beams, grid, done);
  }
  return unique(done);
}

int maxergized(const std::vector<std::string> &grid) {
  int max = 0;
  int xlen = grid.front().length();
  int ylen = grid.size();
  for (int x = 0; x != xlen; ++x) {
    max = std::max(max, energized({x, 0, Dir::South}, grid));
    max = std::max(max, energized({x, ylen - 1, Dir::North}, grid));
  }
  for (int y = 0; y != ylen; ++y) {
    max = std::max(max, energized({0, y, Dir::East}, grid));
    max = std::max(max, energized({xlen - 1, y, Dir::West}, grid));
  }
  return max;
}

int main() {
  std::vector<std::string> grid;
  aoc::foreach("day16.input", [&grid] (std::string line) {
    grid.push_back(line);
  });
  std::cout << "part 1: " << energized({0, 0, Dir::East}, grid) << std::endl;
  std::cout << "part 2: " << maxergized(grid) << std::endl;
  return 0;
}

// part 1: 7434
// part 2: 8183
