#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using Shape = std::string;
//                         oponent  me
using TurnPair = std::pair<Shape,   Shape>;

// Opponent
const Shape oRock = Shape("A");
const Shape oPaper = Shape("B");
const Shape oScissors = Shape("C");

// Me
const Shape mRock = Shape("X");
const Shape mPaper = Shape("Y");
const Shape mScissors = Shape("Z");

std::vector<TurnPair> strategyGuide(std::ifstream& file);
unsigned int getPointsForShape(const Shape& s);
unsigned int getPointsForRoundOutcome(const TurnPair &round);
std::tuple<unsigned int, unsigned int> getPointsForTurn(const TurnPair &round);
Shape iShouldPlay(const TurnPair &round);

int main() {
  std::ifstream file("day2_input.txt");

  if(!file.is_open()) {
    return -1;
  }

  auto strategy = strategyGuide(file);
  
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

std::vector<TurnPair> strategyGuide(std::ifstream& file) {
  std::vector<TurnPair> strategyGuide;
  std::string fileLine;
  while(std::getline(file, fileLine)) {
    std::istringstream iss(fileLine);
    std::string myChoice, opponentChoice;
    if((iss >> myChoice >> opponentChoice)) {
      strategyGuide.push_back({myChoice, opponentChoice});
    } else {
      break;
    }
  }
  return strategyGuide;
}

unsigned int getPointsForShape(const Shape& s) {
  /*
   * X - Rock     - 1 pt
   * Y - Paper    - 2 pt
   * Z - Scissors - 3 pt
   *
   */

  unsigned int retVal{0u};
  
  if (s == mRock) {
    retVal = 1u;
  } else if (s == mPaper) {
    retVal = 2u;
  } else if (s == mScissors) {
    retVal = 3u;
  }

  return retVal;
}

unsigned int getPointsForRoundOutcome(const TurnPair &round) {
  const Shape &opponent = round.first;
  const Shape &me = round.second;

  /*
   * lose 0 pt
   * draw 3 pt
   * win  6 pt
   *
   */

  // Draw scenarios
  if ((me == mRock && opponent == oRock) ||
      (me == mPaper && opponent == oPaper) ||
      (me == mScissors && opponent == oScissors)) {
    return 3u;
  }

  // Win scenarios
  if ((me == mRock && opponent == oScissors) ||
      (me == mScissors && opponent == oPaper) ||
      (me == mPaper && opponent == oRock)) {
    return 6u;
  }

  // The rest are lose scenarios
  return 0u;
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
   * X - I need to lose
   * Y - I need to draw
   * Z - I need to win
   *
   */
  const Shape &oponentChoice = round.first;
  const Shape &desiredResult = round.second;

  if (desiredResult == "X") {
    if (oponentChoice == oRock) {
      return mScissors;
    }
    if (oponentChoice == oScissors) {
      return mPaper;
    }
    if (oponentChoice == oPaper) {
      return mRock;
    }
  }

  if (desiredResult == "Y") {
    if (oponentChoice == oRock) {
      return mRock;
    }
    if (oponentChoice == oScissors) {
      return mScissors;
    }
    if (oponentChoice == oPaper) {
      return mPaper;
    }
  }

  if (desiredResult == "Z") {
    if (oponentChoice == oRock) {
      return mPaper;
    }
    if (oponentChoice == oScissors) {
      return mRock;
    }
    if (oponentChoice == oPaper) {
      return mScissors;
    }
  }
}

