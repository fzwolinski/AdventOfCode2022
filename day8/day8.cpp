#include "file_helpers.h"

#include <iostream>

int main()
{
    std::ifstream file("day8_input.txt");

    if (!file.is_open()) {
        return -1;
    }

    std::vector<std::string> fileData = readFileLineByLine(file);

    const size_t rowsCount = fileData.size();
    const size_t treesInRow = fileData[0].length();
    size_t visibleInCount = 0u;
    size_t maxScenicScore = 0u;

    for (size_t row = 1; row < rowsCount - 1; row++) {
        std::string currentRow = fileData[row];

        for (size_t tree = 1; tree < treesInRow - 1; tree++) {
            int checkedTree = std::stoi(std::string(1, currentRow[tree]));

            // Trees above
            bool isVisibleAbove = true;
            size_t visibleTreesAboveCount = 0u;
            for (int i = row - 1; i >= 0; i--) {
                int treeAbove = std::stoi(std::string(1, fileData[i][tree]));
                if (treeAbove >= checkedTree) {
                    visibleTreesAboveCount++;
                    isVisibleAbove = false;
                    break;
                }
                visibleTreesAboveCount++;
            }

            // Trees below
            bool isVisibleBelow = true;
            size_t visibleTreesBelowCount = 0u;
            for (size_t i = row + 1; i < rowsCount; i++) {
                int treeBelow = std::stoi(std::string(1, fileData[i][tree]));
                if (treeBelow >= checkedTree) {
                    visibleTreesBelowCount++;
                    isVisibleBelow = false;
                    break;
                }
                visibleTreesBelowCount++;
            }

            // Trees to the left
            bool isVisibleToTheLeft = true;
            size_t visibleTreesToTheLeftCount = 0u;
            for (int i = tree - 1; i >= 0; i--) {
                int treeLeft = std::stoi(std::string(1, currentRow[i]));
                if (treeLeft >= checkedTree) {
                    visibleTreesToTheLeftCount++;
                    isVisibleToTheLeft = false;
                    break;
                }
                visibleTreesToTheLeftCount++;
            }

            // Trees to the right
            bool isVisibleToTheRight = true;
            size_t visibleTreesToTheRightCount = 0u;
            for (size_t i = tree + 1; i < treesInRow; i++) {
                int treeRight = std::stoi(std::string(1, currentRow[i]));
                if (treeRight >= checkedTree) {
                    visibleTreesToTheRightCount++;
                    isVisibleToTheRight = false;
                    break;
                }
                visibleTreesToTheRightCount++;
            }

            if (isVisibleAbove ||
                isVisibleBelow ||
                isVisibleToTheLeft ||
                isVisibleToTheRight) {
                visibleInCount++;
            }

            size_t scenicScore = visibleTreesAboveCount * visibleTreesBelowCount * visibleTreesToTheLeftCount * visibleTreesToTheRightCount;
            maxScenicScore = scenicScore > maxScenicScore ? scenicScore : maxScenicScore;
        }
    }

    const size_t visibleOutCount = (treesInRow * 2) + ((rowsCount - 2) * 2);
    const size_t visibleCount = visibleInCount + visibleOutCount;

    std::cout << "With " << visibleOutCount << " trees visible on the edge and another " << visibleInCount 
              << " visible in the interior, a total of " << visibleCount << " trees are visible in this arrangement." << std::endl;
    std::cout << "Highest scenic score possible for any tree is " << maxScenicScore << std::endl;

    return 0;
}
