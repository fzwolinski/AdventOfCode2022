#pragma once

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

std::pair<std::string, std::string> splitStringInHalf(std::string input) {
  const std::string first = input.substr(0, input.length() / 2);
  const std::string second = input.substr(input.length() / 2);

  return std::make_pair(first, second);
}

bool strContainsChar(std::string s, char c) {
  return s.find(c) != std::string::npos;
}

std::vector<char> getSharedUniqueCharacters(std::vector<std::string> strings) {
  const auto& firstStr = strings[0];
  std::vector<char> sharedChars;
  
  bool add = true;
  size_t i = 1u;
  for (const char& c : firstStr) {
    for (size_t i = 1u; i < strings.size(); i++) {
      if (!strContainsChar(strings[i], c)) {
        add = false;
        break;
      }
    }
    if (add) {
      sharedChars.push_back(c);
    }
    add = true;
  }

  sort(sharedChars.begin(), sharedChars.end());
  auto it = std::unique(sharedChars.begin(), sharedChars.end());
  sharedChars.resize(std::distance(sharedChars.begin(), it));

  return sharedChars;
}

