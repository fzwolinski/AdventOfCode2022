#include "file_helpers.h"
#include "string_helpers.h"

#include <fstream>
#include <iostream>
#include <map>
#include <tuple>
#include <utility>

std::map<char, size_t> charPoints {
  {'a',  1},
  {'b',  2},
  {'c',  3},
  {'d',  4},
  {'e',  5},
  {'f',  6},
  {'g',  7},
  {'h',  8},
  {'i',  9},
  {'j', 10},
  {'k', 11},
  {'l', 12},
  {'m', 13},
  {'n', 14},
  {'o', 15},
  {'p', 16},
  {'q', 17},
  {'r', 18},
  {'s', 19},
  {'t', 20},
  {'u', 21},
  {'v', 22},
  {'w', 23},
  {'x', 24},
  {'y', 25},
  {'z', 26},
  {'A', 27},
  {'B', 28},
  {'C', 29},
  {'D', 30},
  {'E', 31},
  {'F', 32},
  {'G', 33},
  {'H', 34},
  {'I', 35},
  {'J', 36},
  {'K', 37},
  {'L', 38},
  {'M', 39},
  {'N', 40},
  {'O', 41},
  {'P', 42},
  {'Q', 43},
  {'R', 44},
  {'S', 45},
  {'T', 46},
  {'U', 47},
  {'V', 48},
  {'W', 49},
  {'X', 50},
  {'Y', 51},
  {'Z', 52}
};

size_t getPointsForChars(std::vector<char> chars);

int main() {
  std::ifstream file("day3_input.txt");

  if (!file.is_open()) {
    return -1;
  }

  std::vector<std::string> fileData = readFileLineByLine(file);
  std::vector<std::pair<std::string, std::string>> listOfItems;
  std::vector<std::tuple<std::string, std::string, std::string>> listOfGroups;
  
  size_t i{1u};
  std::vector<std::string> items;
  for (const auto& line : fileData) {
    auto compartment = splitStringInHalf(line);
    listOfItems.push_back({compartment.first, compartment.second});
    items.push_back(line);
    if (i % 3 == 0) {
      listOfGroups.push_back(std::make_tuple(items[0],
                                             items[1],
                                             items[2]));
      items.clear();
    }
    i++;
  }

  size_t points{0u};
  for (const auto& item : listOfItems) {
    auto sharedChars = getSharedUniqueCharacters(std::vector<std::string> {item.first, 
                                                                           item.second});
    points += getPointsForChars(sharedChars);
  }

  size_t groupsPoints{0u};
  for (const auto& group : listOfGroups) {
    auto sharedChars = getSharedUniqueCharacters(std::vector<std::string> {std::get<0>(group), 
                                                                           std::get<1>(group), 
                                                                           std::get<2>(group)});
    groupsPoints += getPointsForChars(sharedChars);
  }

  std::cout << "Total points: " << points << std::endl;
  std::cout << "Total groups points: " << groupsPoints << std::endl;

  return 0;
}

size_t getPointsForChars(std::vector<char> chars) {
  size_t points{0u};
  for (const char& c : chars) {
    points += charPoints[c];
  }
  return points;
}

