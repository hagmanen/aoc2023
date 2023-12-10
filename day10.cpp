#include "aoc.h"
#include <iostream>
#include <map>

using Coord = std::pair<int, int>;
using Grid = std::map<Coord, char>;
void parseRow(Grid& grid, Coord &start, int y, const std::string& line) {
  for (int x = 0; x != line.length(); ++x) {
    if (line[x] == 'S') {
      start = {x, y};
    }
    if (line[x] != '.') {
      grid[{x, y}] = line[x];
    }
  }
}

char at(const Grid&grid, const Coord& pos) {
  const auto it = grid.find(pos);
  if (it != grid.end()) {
    return it->second;
  }
  return '.';
}

Coord north(const Coord& pos) {
  return {pos.first, pos.second - 1};
}

Coord east(const Coord& pos) {
  return {pos.first + 1, pos.second};
}

Coord south(const Coord& pos) {
  return {pos.first, pos.second + 1};
}

Coord west(const Coord& pos) {
  return {pos.first - 1, pos.second};
}

bool fitNorth(char s, char n) {
  return (s == '|' || s == 'L' || s == 'J') && (n == '|' || n == '7' || n == 'F');
}

bool fitEast(char w, char e) {
  return (w == '-' || w == 'L' || w == 'F') && (e == '-' || e == 'J' || e == '7');
}

bool fitSouth(char n, char s) {
  return fitNorth(s, n);
}

bool fitWest(char e, char w) {
  return fitEast(w, e);
}

bool been(const Grid& visited, const Coord& pos) {
  return visited.find(pos) != visited.end();
}

Coord step(const Grid& grid, Grid& visited, const Coord&pos, const Coord& start) {
  const char cur = at(grid, pos);
  if (!been(visited, north(pos)) && fitNorth(cur, at(grid, north(pos)))) {
    return north(pos);
  }
  if (!been(visited, east(pos)) && fitEast(cur, at(grid, east(pos)))) {
    return east(pos);
  }
  if (!been(visited, south(pos)) && fitSouth(cur, at(grid, south(pos)))) {
    return south(pos);
  }
  if (!been(visited, west(pos)) && fitWest(cur, at(grid, west(pos)))) {
    return west(pos);
  }
  return start;
}

int midStep(const Grid& grid, Grid& visited, const Coord& start) {
  Coord pos = step(grid, visited, start, start);
  visited[start] = '#';
  int steps = 1;
  while (pos != start) {
    visited[pos] = '#';
    pos = step(grid, visited, pos, start);
    ++steps;
  }
  return steps / 2;
}

int count(const Grid &grid, const Grid& visited) {
  int max_x = 0;
  int max_y = 0;
  int c = 0;
  std::vector<char> enter = {};
  for (const auto& p : visited) {
    max_x = std::max(max_x, p.first.first);
    max_y = std::max(max_y, p.first.second);
  }
  for (int i = 0; i != max_y; ++i) {
    bool inside = false;
    for (int j = 0; j != max_x; ++j) {
      const char cur = at(visited, {j, i});
      if (cur ==  '#') {
        const char sym = at(grid, {j, i});
        if (sym == '|') {
          inside = !inside;
        } else if (sym == '-') {
          //nothing;
        } else if (sym == 'F') {
          enter.push_back(sym);
        } else if (sym == 'L') {
          enter.push_back(sym);
        } else if (sym == 'J') {
          if (enter.back() == 'F') {
            inside = !inside;
          }
          enter.pop_back();
        } else if (sym == '7') {
          if (enter.back() == 'L') {
            inside = !inside;
          }
          enter.pop_back();
        }
      } else if (inside) {
        ++c;
      } 
    }
  }
  return c;
}

void adjustStart(Grid &grid, const Coord &start) {
  if(fitNorth('|', at(grid, north(start)))) {
    if(fitEast('-', at(grid, east(start)))) {
      grid[start] = 'L';
      return;
    }
    if(fitSouth('|', at(grid, south(start)))) {
      grid[start] = '|';
      return;
    }
    grid[start] = 'J';
    return;
  }
  if (fitEast('-', at(grid, east(start)))) {
    if(fitSouth('|', at(grid, south(start)))) {
      grid[start] = 'F';
      return;
    }
    grid[start] = '-';
    return;
  }
  grid[start] = '7';
}

int main() {
  Grid grid;
  Coord start;
  int y = 0;
  int x = 0;

  aoc::foreach("day10.input", [&grid, &start, &y, &x] (std::string line) {
    parseRow(grid, start, y++, line);
    x = line.length();
  });
  adjustStart(grid, start);
  Grid visited;
  std::cout << "part 1: " << midStep(grid, visited, start) << std::endl;
  std::cout << "part 2: " << count(grid, visited) << std::endl;
  return 0;
}

// part 1: 6882
// part 2: 491
