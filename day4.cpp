#include "aoc.h"
#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <numeric>

int gameScore1(const std::set<int> &winners, const std::set<int> &yours) {
  auto fun = [&yours] (int acc, int w) {
    if (yours.find(w) != yours.end()) {
      if (acc) {
        return acc *= 2;
      }
      return 1;
    }
    return acc;
  };
  return std::accumulate(winners.begin(), winners.end(), 0, std::move(fun));
}

int gameScore2(const std::set<int> &winners, const std::set<int> &yours) {
  auto fun = [&yours] (int acc, int w) { return acc + (yours.find(w) != yours.end() ? 1 : 0);};
  return std::accumulate(winners.begin(), winners.end(), 0, std::move(fun));
}

int cardNumber(const std::string& line) {
  return std::stoi(aoc::split(line, " ")[1]);
}

void game2(std::map<int, int> &cards, int card, const std::set<int> &winners, const std::set<int> &yours) {
  const int tickets = ++cards[card];
  const int score = gameScore2(winners, yours);
  for (int p = 0; p != score; ++p) {
    cards[card + p + 1] += tickets;
  }
}

int main() {
  int sum1 = 0;
  std::map<int, int> cards;
  aoc::foreach("day4.input", [&sum1, &cards] (std::string line) {
    const auto game = aoc::split(line, ": ");
    const auto numbers = aoc::split(game[1], " | ");
    const auto winners = aoc::intset(aoc::split(numbers[0], " "));
    const auto yours = aoc::intset(aoc::split(numbers[1], " "));
    sum1 += gameScore1(winners, yours);
    game2(cards, cardNumber(game[0]), winners, yours);
  });
  auto fun = [](int acc, const auto& p) { return acc + p.second; };
  int sum2 = std::accumulate(cards.begin(), cards.end(), 0, std::move(fun));
  std::cout << "part 1: " << sum1 << std::endl;
  std::cout << "part 2: " << sum2 << std::endl;
  return 0;
}

// part 1: 26426
// part 2: 6227972