#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> eachReindeerCalories(std::ifstream& file) {
  std::string fileLine;
  std::vector<int> reindeers;
  int currReindeerCalories{0};

  while(std::getline(file, fileLine)) {
    std::istringstream iss(fileLine);
    int lineNum;
    if(!(iss >> lineNum)) {
      reindeers.push_back(currReindeerCalories);
      currReindeerCalories = 0;
      continue;
    }
    currReindeerCalories += lineNum;
  }

  // Process last line
  reindeers.push_back(currReindeerCalories);    
  
  return reindeers;
}

int getTopThreeSum(std::vector<int> const &sortedVec) {
  int topThreeSum{0};

  const size_t vecSize = sortedVec.size();
  topThreeSum += sortedVec.at(vecSize-1);
  topThreeSum += sortedVec.at(vecSize-2);
  topThreeSum += sortedVec.at(vecSize-3);

  return topThreeSum;
}

int main() {
  std::ifstream file("day1_input.txt");
  
  if(!file.is_open()) {
    return -1;
  }

  std::vector<int> reindeerCalories = eachReindeerCalories(file); 
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

