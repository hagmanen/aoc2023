#include "aoc.h"
#include <iostream>
#include <vector>
#include <map>

struct Game {
  int id;
  std::map<std::string, int> max_seen;
};

int parseGameId(const std::string& line) {
  return std::stoi(line.substr(line.find(" ") + 1, line.size()));
}

void parseColor(std::map<std::string, int> &r, const std::string &line) {
  const auto color = aoc::split(line, " ");
  int amount = std::stoi(color[0]);
  if (r[color[1]] < amount) {
    r[color[1]] = amount;
  }
}

void parseCubes(std::map<std::string, int> &r, const std::string &line) {
  for (const auto &color : aoc::split(line, ", ")) {
    parseColor(r, color);
  }
}

std::map<std::string, int> parseSets(const std::string& line) {
  std::map<std::string, int> r;
  for (const auto &cube : aoc::split(line, "; ")) {
    parseCubes(r, cube);
  }
  return r;
}

Game parseLine(const std::string& line) {
  Game g;
  const auto gam = aoc::split(line, ": ");
  g.id = parseGameId(gam[0]);
  g.max_seen = parseSets(gam[1]);
  return g;
}

int main() {
  int sum1 = 0;
  int sum2 = 0;
  aoc::foreach("day2.input", [&sum1, &sum2] (std::string line) {
    auto game = parseLine(line);
    if (game.max_seen["red"] <= 12 &&game.max_seen["green"] <= 13 && game.max_seen["blue"] <= 14) {
      sum1 += game.id;
    }
    sum2 += game.max_seen["red"] * game.max_seen["green"] * game.max_seen["blue"];
  });
  std::cout << "part 1: " << sum1 << std::endl;
  std::cout << "part 2: " << sum2 << std::endl;
  return 0;
}

// part 1: 1867
// part 2: 84538