#include "file_helpers.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> eachReindeerCalories(const std::vector<std::string> &data);
int getTopThreeSum(std::vector<int> const &sortedVec);

int main() {
  std::ifstream file("day1_input.txt");
  
  if(!file.is_open()) {
    return -1;
  }

  std::vector<std::string> fileData = readFileLineByLine(file);
  std::vector<int> reindeerCalories = eachReindeerCalories(fileData); 
  std::sort(reindeerCalories.begin(), reindeerCalories.end());

  const int maxCalories = reindeerCalories.back();
  const int topThreeSum = getTopThreeSum(reindeerCalories); 

  std::cout << "Max calories: " << maxCalories << "\n";
  std::cout << "Sum of top three: " << topThreeSum << "\n\n";

  std::cout << "Some statistics:\n";

  for(size_t i = 0; i < reindeerCalories.size(); i++) {
    std::cout << "Reindeer " << i << ": " << reindeerCalories[i] << " kcal\n";
    if (i == 5) {
      std::cout << "... let's not print all of them\n";
      break;
    }
  }

  return 0;
}

int getTopThreeSum(std::vector<int> const &sortedVec) {
  int topThreeSum{0};

  const size_t vecSize = sortedVec.size();
  topThreeSum += sortedVec.at(vecSize-1);
  topThreeSum += sortedVec.at(vecSize-2);
  topThreeSum += sortedVec.at(vecSize-3);

  return topThreeSum;
}

std::vector<int> eachReindeerCalories(const std::vector<std::string> &data) {
  std::vector<int> reindeers;
  int currReindeerCalories{0};
  std::string line{data.front()};

  for (size_t i = 0; i < data.size(); i++) {
    line = data[i];
    int lineNum;
    std::istringstream iss(line);
    if (!(iss >> lineNum)) {
      reindeers.push_back(currReindeerCalories);
      currReindeerCalories = 0;
      continue;
    }
    currReindeerCalories += lineNum;
  }

  reindeers.push_back(currReindeerCalories);  
  return reindeers;
}

