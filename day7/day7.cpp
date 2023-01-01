#include "file_helpers.h"
#include "string_helpers.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

// Part 1
const size_t FIND_DIR_SIZE_MAX = 100'000;

// Part 2
const size_t TOTAL_DISK_SPACE = 70'000'000;
const size_t NEEDED_UNUSED_SPACE = 30'000'000;

enum class CMD {
    CD,
    LS,
    DIR_NAME,
    FILE_NAME,
};

CMD getCommand(const std::string& str);
std::string getDirName(const std::string& dirCmd);
std::string getUpDirPath(const std::string& dirPath);
std::pair<std::string, size_t> getFileNameAndSize(const std::string& file);
std::vector<std::string> getAllDirsFromFilePath(const std::string& filePath);

int main() {
    std::ifstream file("day7_input.txt");

    if (!file.is_open()) {
        return -1;
    }

    std::vector<std::string> fileData = readFileLineByLine(file);
    std::vector<std::pair<std::string, size_t>> files;
    std::string currDir = "/";

    for (std::string line : fileData) {
        CMD cmd = getCommand(line);

        switch (cmd) {
        case CMD::LS:
        case CMD::DIR_NAME:
            break;
        case CMD::CD:
            if (const std::string dirName = getDirName(line); dirName != "..") {
                if (dirName != "/") {
                    currDir += dirName.c_str() + std::string("/");
                }
            }
            else {
                currDir = getUpDirPath(currDir);
            }
            break;
        case CMD::FILE_NAME:
            auto [fName, fSize] = getFileNameAndSize(line);
            files.push_back(std::make_pair(currDir + fName, fSize));
            break;
        }
    }

    std::map<std::string, size_t> dirs;
    for (auto f : files) {
        auto allDirs = getAllDirsFromFilePath(f.first);

        for (auto dir : allDirs) {
            dirs[dir] += f.second;
        }
    }

    std::vector<size_t> dirSizes;
    size_t part1Sum{ 0u };

    for (auto dir : dirs) {
        dirSizes.push_back(dir.second);
        if (dir.second <= FIND_DIR_SIZE_MAX) {
            part1Sum += dir.second;
        }
    }

    std::sort(dirSizes.begin(), dirSizes.end());
    
    const size_t usedSpaceTotal = dirs["/"];
    const size_t currentUnusedSpace = TOTAL_DISK_SPACE - usedSpaceTotal;
    const size_t needToFree = NEEDED_UNUSED_SPACE - currentUnusedSpace;
    
    size_t deletedDirSize{ 0u };

    for (auto dirSize : dirSizes) {
        if (dirSize >= needToFree) {
            deletedDirSize = dirSize;
            break;
        }
    }

    std::cout << "[Part 1] Sum of the total sizes of directories <= " << FIND_DIR_SIZE_MAX << " is " << part1Sum << "\n";
    std::cout << "[Part 2] Total size of deleted directory is " << deletedDirSize << "\n";

    return 0;
}

CMD getCommand(const std::string& str) {
    if (hasSubStr(str, "$ cd")) {
        return CMD::CD;
    } else if (hasSubStr(str, "dir ")) {
        return CMD::DIR_NAME;
    } else if (hasSubStr(str, "$ ls")) {
        return CMD::LS;
    }

    return CMD::FILE_NAME;
}

std::string getDirName(const std::string& dirCmd) {
    // dirCmd param format: "$ cd dir1"
    // return: "dir1"
    size_t cmdLen = std::string("$ cd ").length();
    return dirCmd.substr(cmdLen, dirCmd.length() - cmdLen);
}

std::string getUpDirPath(const std::string& dirPath) {
    // dirPath param format: "/dir1/dir2/dir3/"
    // return: "/dir1/dir2/"

    size_t shashPos = dirPath.rfind("/", dirPath.length() - 2);
    std::string upDirPath = shashPos == 0 ? "/" : dirPath.substr(0, shashPos + 1);
    return upDirPath;
}

std::vector<std::string> getAllDirsFromFilePath(const std::string& filePath) {
    // filePath param format: "/dir1/dir2/dir3/file.txt"
    // return: ["/", "/dir1/", "/dir1/dir2/", "/dir1/dir2/dir3/"]

    std::vector<size_t> positions;
    for (size_t i = 0; i < filePath.size(); i++) {
        if (filePath[i] == '/') {
            positions.push_back(i);
        }
    }

    std::vector<std::string> allDirs;
    for (auto position : positions) {
        allDirs.push_back(filePath.substr(0, position + 1));
    }

    return allDirs;
}

std::pair<std::string, size_t> getFileNameAndSize(const std::string& file) {
    // file param format: 8504156 file.txt
    // return: ("file.txt", 8504156)

    size_t namePos = file.find(" ");
    size_t fileSize = std::stoi(file.substr(0, namePos));
    std::string fileName = file.substr(namePos + 1, file.length());

    return std::make_pair(fileName, fileSize);
}
