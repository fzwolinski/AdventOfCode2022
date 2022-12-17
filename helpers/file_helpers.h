#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include <vector>

std::vector<std::string> readFileLineByLine(std::ifstream &file) {
  std::vector<std::string> fileData;  
  std::string line;
  while (std::getline(file, line)) {
    fileData.push_back(line);
  }

  return fileData;
}

std::string readFileBuffer(const std::ifstream &file) {
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

