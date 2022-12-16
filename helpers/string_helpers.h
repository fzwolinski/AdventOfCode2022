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

std::vector<std::string> splitStr(const std::string& fullString, 
                                  const std::string& delimiter) {
  std::vector<std::string> outList;
  const auto& d = delimiter;

  std::string toSplit = fullString;
  size_t pos = toSplit.find(d);
  while (std::string::npos != pos) {
    outList.push_back(toSplit.substr(0, pos));
    toSplit.erase(0, pos + d.length());
    pos = toSplit.find(d);
  }

  outList.push_back(toSplit.substr(0, toSplit.find(d)));

  return outList;
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
