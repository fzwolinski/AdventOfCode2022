#include "file_helpers.h"
#include "string_helpers.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <tuple>

using move = std::tuple<unsigned int, unsigned int, unsigned int>;

// [Z] [M] [P]
//  <--->
//    5  (but we index stacks from 1 so 5 - 1 = 4)
const unsigned int CRATES_DISTANCE = 4;
const unsigned int NUM_OF_STACKS = 9;

void pushCratesToStacks(std::vector<std::vector<std::string>>& stacks, const std::string& str);
move parseMoveLine(const std::string& line);
void makeMove9000(std::vector<std::vector<std::string>>& stacks, move currMove);
void makeMove9001(std::vector<std::vector<std::string>>& stacks, move currMove);
std::string getTopStacksMsg(const std::vector<std::vector<std::string>>& stacks);

int main() {
  std::ifstream file("day5_input.txt");

  if (!file.is_open()) {
    return -1;
  }

  std::vector<std::string> fileData = readFileLineByLine(file);
  std::vector<std::string> stacksRawData;
  std::vector<std::string> movesRawData;

  bool readStacks = true;
  bool readMoves = false;
  for (const auto& line : fileData) {
    if (containsNum(line)) {
      readStacks = false;
    }

    if (readStacks) {
      stacksRawData.push_back(line);
    }

    if (line.empty()) {
      readMoves = true;
      continue;
    }

    if (readMoves) {
      movesRawData.push_back(line);
    }
  }

  std::reverse(stacksRawData.begin(), stacksRawData.end());
  std::vector<std::vector<std::string>> stacks9000(NUM_OF_STACKS + 1); // index 1-9
  std::vector<std::vector<std::string>> stacks9001(NUM_OF_STACKS + 1); // index 1-9
  for (const auto& line : stacksRawData) {
    pushCratesToStacks(stacks9000, line);
    pushCratesToStacks(stacks9001, line);
  }

  for (const auto& m : movesRawData) {
    auto currMove = parseMoveLine(m);
    makeMove9000(stacks9000, currMove);
    makeMove9001(stacks9001, currMove);
  }

  auto topStacks9000Msg = getTopStacksMsg(stacks9000);
  auto topStacks9001Msg = getTopStacksMsg(stacks9001);
  std::cout << "Top stacks CrateMover 9000 message: " << topStacks9000Msg << "\n";
  std::cout << "Top stacks CrateMover 9001 message: " << topStacks9001Msg << "\n";

  return 0;
}

void pushCratesToStacks(std::vector<std::vector<std::string>>& stacks, const std::string& str) {
  size_t stackPos = 1;
  for (size_t i = 1; i < str.length(); i += CRATES_DISTANCE) {
    if (str[i] != ' ') {
      stacks[stackPos++].push_back(std::string(1, str[i]));
    } else {
      stackPos++;
    }
  }
}

move parseMoveLine(const std::string& line) {
  unsigned int numOfCrates{0u};
  unsigned int from{0u};
  unsigned int to{0u};

  const auto fromPos = line.find("from");
  const auto toPos = line.find("to");

  // move x
  // <--->
  //   5
  numOfCrates = std::stoi(line.substr(5, 2));
  from = std::stoi(line.substr(fromPos + std::string("from ").length(), 2));
  to = std::stoi(line.substr(toPos + std::string("to ").length(), 2));

  return std::make_tuple(numOfCrates, from, to);
}

void makeMove9000(std::vector<std::vector<std::string>>& stacks, move currMove) {
  unsigned int numOfCrates = std::get<0>(currMove);
  unsigned int from = std::get<1>(currMove);
  unsigned int to = std::get<2>(currMove);

  size_t cratesOnStack = stacks[from].size();
  for (size_t i = 0; i < numOfCrates; i++) {
    stacks[to].push_back(stacks[from][cratesOnStack - 1 - i]);
    stacks[from].pop_back();
  }
}

void makeMove9001(std::vector<std::vector<std::string>>& stacks, move currMove) {
  unsigned int numOfCrates = std::get<0>(currMove);
  unsigned int from = std::get<1>(currMove);
  unsigned int to = std::get<2>(currMove);

  std::vector<std::string> movedStacks;
  size_t cratesOnStack = stacks[from].size();
  for (size_t i = 0; i < numOfCrates; i++) {
    movedStacks.push_back(stacks[from][cratesOnStack - 1 - i]);
    stacks[from].pop_back();
  }

  std::reverse(movedStacks.begin(), movedStacks.end());

  for (const auto& movedStack : movedStacks) {
    stacks[to].push_back(movedStack);
  }
}

std::string getTopStacksMsg(const std::vector<std::vector<std::string>>& stacks) {
  std::string msg;
  for (const auto stack : stacks) {
    if (stack.size() > 0) {
      msg += stack[stack.size() - 1];
    }
  }

  return msg;
}
