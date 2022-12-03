#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

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
unsigned int getPointsForTurn(const TurnPair &round);

int main() {
  std::ifstream file("day2_input.txt");

  if(!file.is_open()) {
    return -1;
  }

  auto strategy = strategyGuide(file);
  
  unsigned int myScore{0u};
  for (TurnPair turn : strategy) {
    myScore += getPointsForTurn(turn);
  }
  
  std::cout << "My score: " << myScore << "\n";

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

unsigned int getPointsForTurn(const TurnPair &round) {
  unsigned int points{0u};
  // Points for the shape I selected
  points += getPointsForShape(round.second);
  
  // Points for the outcome of the round
  points += getPointsForRoundOutcome(round);

  return points;
}

