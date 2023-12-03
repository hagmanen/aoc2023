#include "aoc.h"
#include <iostream>
#include <vector>
#include <map>

struct Symbol {
  char symbol;
  int y;
  int x;
  Symbol(char symbol, int y, int x): symbol(symbol), y(y), x(x) {}
};

struct Number {
  int number;
  const int y;
  int x_min;
  int x_max;
  bool started;
  Number(int y) : number(0), y(y), x_min(0), x_max(0), started(false) {}
  void append(int x, int n) {
    if (started) {
      ++x_max;
      number = number * 10 + n;
    } else {
      started = true;
      x_min = x_max = x;
      number = n;
    }
  }
  bool isNeighbor(const Symbol& s) const {
    if (std::abs(y - s.y) > 1) {
      return false;
    }
    return s.x >= (x_min - 1) && s.x <= (x_max + 1);
  }
};

void parseLine(const std::string &line, std::vector<Symbol> &symbols, std::vector<Number> &numbers, int y) {
  Number current(y);
  for (int x = 0; x != line.size(); ++x) {
    if (line[x] >= '0' && line[x] <= '9') {
      current.append(x, line[x] - '0');
      continue;
    }
    if (current.started) {
      numbers.push_back(current);
      current.started = false;
    }
    if (line[x] != '.') {
      symbols.emplace_back(Symbol(line[x], y, x));
    }
  }
  if (current.started) {
    numbers.push_back(current);
  }
}

int sumNeighbors(const std::vector<Symbol>& symbols, std::vector<Number> &numbers) {
  int sum = 0;
  for (const auto& number : numbers) {
    for (const auto& symbol : symbols) {
      if (number.isNeighbor(symbol)) {
        sum += number.number;
        break;
      }
    }
  }
  return sum;
}

int gearRatio(const Symbol& gear, std::vector<Number> &numbers) {
  int ratio = 1;
  int neigbours = 0;
  for (const auto& number : numbers) {
    if (number.isNeighbor(gear)) {
      ratio *= number.number;
      ++neigbours;
    }
  }
  if (neigbours == 2) {
    return ratio;
  }
  return 0;
}

int gearRatios(const std::vector<Symbol>& symbols, std::vector<Number> &numbers) {
  int sum = 0;
  for (const auto& symbol : symbols) {
    if (symbol.symbol == '*') {
      sum += gearRatio(symbol, numbers);
    }
  }
  return sum;
}

int main() {
  std::vector<Symbol> symbols;
  std::vector<Number> numbers;
  int y = 0;
  aoc::foreach("day3.input", [&symbols, &numbers, &y] (std::string line) {
    parseLine(line, symbols, numbers, y++);
  });
  std::cout << "part 1: " << sumNeighbors(symbols, numbers) << std::endl;
  std::cout << "part 2: " << gearRatios(symbols, numbers) << std::endl;
  return 0;
}

// part 1: 527446
// part 2: 73201705