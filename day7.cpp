#include "aoc.h"
#include <iostream>
#include <vector>
#include <algorithm>

struct Hand {
  int type;
  int joker_type;
  std::vector<int> cards;
  int bid;
};

int parseCard(char c) {
  if(c >= '0' && c <= '9') {
    return c - '0';
  }
  switch(c) {
    case 'T': return 10;
    case 'J': return 11;
    case 'Q': return 12;
    case 'K': return 13;
  }
  return 14;
}
constexpr int kFiveOfAKind = 6;
constexpr int kFourOfAKind = 5;
constexpr int kFullHouse = 4;
constexpr int kThreeOfAKind = 3;
constexpr int kTwoPairs = 2;
constexpr int kOnePair = 1;
constexpr int kHighCard = 0;

int typeOfHand(std::vector<int> cards) {
  std::sort(cards.begin(), cards.end());
  int c1 = cards[0];
  int c2 = cards[1];
  int c3 = cards[2];
  int c4 = cards[3];
  int c5 = cards[4];
  if (c1 == c2) {
    if (c2 == c3) {
      if (c3 == c4) {
        if (c4 == c5) {
          return kFiveOfAKind;
        }
        return kFourOfAKind;
      }
      if (c4 == c5) {
        return kFullHouse;
      }
      return kThreeOfAKind;
    }
    if (c3 == c4) {
      if (c4 == c5) {
        return kFullHouse;
      }
      return kTwoPairs;
    }
    if (c4 == c5) {
      return kTwoPairs;
    }
    return kOnePair;
  }
  // First card unique
  if (c2 == c3) {
    if (c3 == c4) {
      if (c4 == c5) {
        return kFourOfAKind;
      }
      return kThreeOfAKind;
    }
    if (c4 == c5) {
      return kTwoPairs;
    }
    return kOnePair;
  }
  // Two first unique
  if(c3 == c4) {
    if (c4 == c5) {
      return kThreeOfAKind;
    }
    return kOnePair;
  }
  if (c4 == c5) {
    return kOnePair;
  }
  return kHighCard;
}

std::vector<int> replaceJoker(const std::vector<int>& hand, int card) {
  std::vector<int> joker_hand;
  std::transform(hand.begin(), hand.end(), std::back_inserter(joker_hand), [card] (int hc) {return (11 == hc) ? card : hc;});
  return joker_hand;
}

Hand parseHand(const std::string& line) {
  Hand hand;
  const auto hb = aoc::split(line, " ");
  bool has_joker = false;
  for (const auto c : hb[0]) {
    if (c == 'J') {
      has_joker = true;
    }
    hand.cards.push_back(parseCard(c));
  }
  hand.bid = std::stoi(hb[1]);
  hand.type = typeOfHand(hand.cards);
  hand.joker_type = hand.type;
  if (has_joker) {
    for (int jk = 2; jk != 15; ++jk) {
      const auto jh = replaceJoker(hand.cards, jk);
      const auto jt = typeOfHand(jh);

      hand.joker_type = std::max(hand.joker_type, jt);
    }
  }
  return hand;
}

bool compareHands(const Hand& lhs, const Hand& rhs) {
  if (lhs.type == rhs.type) {
    for (int i = 0; i != 5; ++i) {
      if (lhs.cards[i] == rhs.cards[i]) { continue; }
      return lhs.cards[i] < rhs.cards[i];
    }
    return false;
  }
  return lhs.type < rhs.type;
}

bool compareJokerHands(const Hand& lhs, const Hand& rhs) {
  if (lhs.joker_type == rhs.joker_type) {
    for (int i = 0; i != 5; ++i) {
      if (lhs.cards[i] == rhs.cards[i]) { continue; }
      if (lhs.cards[i] == 11) {
        return true;
      }
      if (rhs.cards[i] == 11) {
        return false;
      }
      return lhs.cards[i] < rhs.cards[i];
    }
    return false;
  }
  return lhs.joker_type < rhs.joker_type;
}

uint64_t winnings(const std::vector<Hand>& hands) {
  uint64_t r = 0;
  for (size_t i = 0; i != hands.size(); ++i) {
    r += ((i+1) * hands[i].bid);
  }
  return r;
}

int main() {
  std::vector<Hand> hands;
  aoc::foreach("day7.input", [&hands] (std::string line) {
    hands.emplace_back(parseHand(line));
  });
  std::sort(hands.begin(), hands.end(), compareHands);
  std::cout << "part 1: " << winnings(hands) << std::endl;
  std::sort(hands.begin(), hands.end(), compareJokerHands);
  std::cout << "part 2: " << winnings(hands) << std::endl;
  return 0;
}

// part 1: 246409899
// part 2: 244848487
