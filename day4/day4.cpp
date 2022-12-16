#include "file_helpers.h"
#include "string_helpers.h"

#include <fstream>
#include <iostream>

using range = std::pair<int, int>;

bool rangeOverlapsRange(const std::vector<range>& sections);
bool rangeFullyContainsRange(const std::vector<range>& sections);
std::vector<range> getSections(const std::string& input);

int main() {
  std::ifstream file("day4_input.txt");

  if (!file.is_open()) {
    return -1;
  }

  std::vector<std::string> fileData = readFileLineByLine(file);
  std::vector<int> sections;

  size_t overlapPairs{0u};
  size_t fullOverlapPairs{0u};

  for (const auto &line : fileData) {
    std::vector<range> sections = getSections(line);

    if (rangeFullyContainsRange(sections)) {
      fullOverlapPairs++;
    }

    if (rangeOverlapsRange(sections)) {
      overlapPairs++;
    }

    sections.clear();
  }

  std::cout << "Number of ranges fully containing other ranges: " << fullOverlapPairs << "\n";
  std::cout << "Number of ranges overlaping other ranges: " << overlapPairs << "\n";

  return 0;
}

bool rangeOverlapsRange(const std::vector<range>& sections) {
  const auto& s1Start = std::get<0>(sections[0]);
  const auto& s1End   = std::get<1>(sections[0]);
  const auto& s2Start = std::get<0>(sections[1]);
  const auto& s2End   = std::get<1>(sections[1]);

  if (s1Start <= s2End && s2Start <= s1End) {
    return true;
  }

  return false;
}

bool rangeFullyContainsRange(const std::vector<range>& sections) {
  const auto& s1Start = std::get<0>(sections[0]);
  const auto& s1End   = std::get<1>(sections[0]);
  const auto& s2Start = std::get<0>(sections[1]);
  const auto& s2End   = std::get<1>(sections[1]);

  // If s1 is in s2
  if (s1Start >= s2Start && s1End <= s2End) {
    return true;
  }

  // If s2 is in s1
  if (s2Start >= s1Start && s2End <= s1End) {
    return true;
  }
  
  return false;
}

std::vector<range> getSections(const std::string& input) {
  // input has format "2-3,4-5" 

  // First split - by ","
  std::vector<std::string> sectionSplitByDash = splitStr(input, ",");

  // Second split - by "-"
  std::vector<std::string> s1Range = splitStr(sectionSplitByDash[0], "-");
  std::vector<std::string> s2Range = splitStr(sectionSplitByDash[1], "-");

  std::pair<int, int> firstPair = std::make_pair(std::stoi(s1Range[0]),
                                                 std::stoi(s1Range[1]));
  std::pair<int, int> secondPair = std::make_pair(std::stoi(s2Range[0]),
                                                 std::stoi(s2Range[1]));

  return std::vector<range>{firstPair, secondPair};
}
