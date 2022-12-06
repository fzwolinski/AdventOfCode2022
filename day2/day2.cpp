#include "helpers.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

enum class Shape {
  rock = 1,
  paper = 2,
  scissors = 3
};

enum class Result {
  loss = 0,
  draw = 3,
  win = 6
};

using Short = std::string;

std::map<Short, Shape> shapeMap {
  {"X", Shape::rock},
  {"Y", Shape::paper},
  {"Z", Shape::scissors},
  {"A", Shape::rock},
  {"B", Shape::paper},
  {"C", Shape::scissors}
};

//                         oponent  me
using TurnPair = std::pair<Shape,   Shape>;

std::vector<TurnPair> parseFileData(const std::vector<std::string> &fileData);
Shape getShapeFromShort(const Short &_short);
unsigned int getPointsForShape(const Shape& s);
unsigned int getPointsForRoundOutcome(const TurnPair &round);
std::tuple<unsigned int, unsigned int> getPointsForTurn(const TurnPair &round);
Shape iShouldPlay(const TurnPair &round);

int main() {
  std::ifstream file("day2_input.txt");

  if (!file.is_open()) {
    return -1;
  }

  std::vector<std::string> fileData = readFileLineByLine(file);
  std::vector<TurnPair> strategy = parseFileData(fileData);
 
  unsigned int scoreStrategyGuide{0u};
  unsigned int scoreDesiredOutcome{0u};
  
  for (TurnPair turn : strategy) {
    auto [temp1, temp2] = getPointsForTurn(turn);
    scoreStrategyGuide += temp1;
    scoreDesiredOutcome += temp2;
  }
  
  std::cout << "Total score: " << scoreStrategyGuide << "\n";
  std::cout << "Total score with desired outcome: " << scoreDesiredOutcome << "\n";

  return 0;
}

std::vector<TurnPair> parseFileData(const std::vector<std::string> &data) {
  std::vector<TurnPair> strategyGuide;
  
  for (auto &line : data) {
    std::istringstream iss(line);
    Short myChoice, opponentChoice;
    if (iss >> myChoice >> opponentChoice) {
      strategyGuide.push_back({getShapeFromShort(myChoice), 
                               getShapeFromShort(opponentChoice)});
    }
  }

  return strategyGuide;
}

Shape getShapeFromShort(const Short &_short) {
  return shapeMap.at(_short);
}

unsigned int getPointsForShape(const Shape& s) {
  return static_cast<unsigned int>(s);
}

unsigned int getPointsForRoundOutcome(const TurnPair &round) {
  const Shape &opponent = round.first;
  const Shape &me = round.second;

  // Draw scenarios
  if ((me == Shape::rock && opponent == Shape::rock) ||
      (me == Shape::paper && opponent == Shape::paper) ||
      (me == Shape::scissors && opponent == Shape::scissors)) {
    return static_cast<unsigned int>(Result::draw);
  }

  // Win scenarios
  if ((me == Shape::rock && opponent == Shape::scissors) ||
      (me == Shape::scissors && opponent == Shape::paper) ||
      (me == Shape::paper && opponent == Shape::rock)) {
    return static_cast<unsigned int>(Result::win);
  }

  // The rest are loss scenarios
  return static_cast<unsigned int>(Result::loss);  
}

std::tuple<unsigned int, unsigned int> getPointsForTurn(const TurnPair &round) {
  unsigned int points{0u};
  unsigned int pointsDesiredReturn{0u};
  const Shape shapeIShouldPlay = iShouldPlay(round);
  const TurnPair desiredTurn{round.first, shapeIShouldPlay};

  // Points for the shape I selected
  points += getPointsForShape(round.second);
  pointsDesiredReturn += getPointsForShape(shapeIShouldPlay);
  
  // Points for the outcome of the round
  points += getPointsForRoundOutcome(round);
  pointsDesiredReturn += getPointsForRoundOutcome(desiredTurn);

  return {points, pointsDesiredReturn};
}

Shape iShouldPlay(const TurnPair &round) {
  /*
   * X - Rock     - I need to loss
   * Y - Paper    - I need to draw
   * Z - Scissors - I need to win
   *
   */

  const Shape &oponentChoice = round.first;
  const Shape &desiredResult = round.second;

  if (desiredResult == Shape::rock) {
    if (oponentChoice == Shape::rock) {
      return Shape::scissors;
    }
    if (oponentChoice == Shape::scissors) {
      return Shape::paper;
    }
    if (oponentChoice == Shape::paper) {
      return Shape::rock;
    }
  }

  if (desiredResult == Shape::paper) {
    if (oponentChoice == Shape::rock) {
      return Shape::rock;
    }
    if (oponentChoice == Shape::scissors) {
      return Shape::scissors;
    }
    if (oponentChoice == Shape::paper) {
      return Shape::paper;
    }
  }

  if (desiredResult == Shape::scissors) {
    if (oponentChoice == Shape::rock) {
      return Shape::paper;
    }
    if (oponentChoice == Shape::scissors) {
      return Shape::rock;
    }
    if (oponentChoice == Shape::paper) {
      return Shape::scissors;
    }
  }
}

