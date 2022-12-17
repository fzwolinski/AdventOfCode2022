#include "file_helpers.h"
#include "string_helpers.h"

#include <algorithm>
#include <fstream>
#include <iostream>

size_t getMarkerPosition(const std::string& str, const size_t& numUnqChars);

int main() {
  std::ifstream file("day6_input.txt");

  if (!file.is_open()) {
    return -1;
  }

  const std::string fileData = readFileBuffer(file);
  size_t markerPosition4 = getMarkerPosition(fileData, 4);
  size_t markerPosition14 = getMarkerPosition(fileData, 14);  

  std::cout << "First marker position [ 4]: " << markerPosition4 << std::endl;
  std::cout << "First marker position [14]: " << markerPosition14 << std::endl;

  return 0; 
}

size_t getMarkerPosition(const std::string& str, const size_t& numUnqChars) {
  size_t markerPos = 0;
  while (!allUniqueChars(str.substr(markerPos, numUnqChars))) {
    markerPos++;
  }
  return markerPos + numUnqChars;
}

