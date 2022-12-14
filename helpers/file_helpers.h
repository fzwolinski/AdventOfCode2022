#pragma once

#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> readFileLineByLine(std::ifstream &file) {
  std::vector<std::string> fileData;  
  std::string line;
  while (std::getline(file, line)) {
    fileData.push_back(line);
  }

  return fileData;
}


