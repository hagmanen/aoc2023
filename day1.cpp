
#include "aoc.h"
#include <iostream>
#include <regex>

int getValue(const std::string& line) {
  auto is_digit = [] (char i) { return i >= '0' && i <= '9';};
  auto first = *std::find_if(line.begin(), line.end(), is_digit);
  auto second = *std::find_if(line.rbegin(), line.rend(), is_digit);
  auto res =  (first - '0') * 10 + (second - '0');
  return res;
}

void fixLine(std::string &line) {
  line = std::regex_replace(line, std::regex("one"), "one1one");
  line = std::regex_replace(line, std::regex("two"), "two2two");
  line = std::regex_replace(line, std::regex("three"), "three3three");
  line = std::regex_replace(line, std::regex("four"), "four4four");
  line = std::regex_replace(line, std::regex("five"), "five5five");
  line = std::regex_replace(line, std::regex("six"), "six6six");
  line = std::regex_replace(line, std::regex("seven"), "seven7seven");
  line = std::regex_replace(line, std::regex("eight"), "eight8eight");
  line = std::regex_replace(line, std::regex("nine"), "nine9nine");
}

int main() {
  int sum1 = 0;
  int sum2 = 0;
  aoc::foreach("day1.input", [&sum1, &sum2] (std::string line) {
    if(!line.empty()) {
      sum1 += getValue(line);
      fixLine(line);
      sum2 += getValue(line);
    }
  });
  std::cout << "part 1: " << sum1 << std::endl;
  std::cout << "part 2: " << sum2 << std::endl;
  return 0;
}

// part 1: 56042
// part 2: 55358