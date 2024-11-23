#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<int> availableResources;
std::vector<std::vector<int>> maxProcessResources;
std::vector<std::vector<int>> allocatedProcessResources;
std::vector<std::vector<int>> neededProcessResources;

int processFile(std::ifstream inputFile);
std::vector<int> getSafeState();
std::vector<std::string> splitString(std::string str, char splitter);
bool hasFalseEntry(std::vector<bool>);
bool vectorLTE(std::vector<int> lhs, std::vector<int> rhs);

int main(int argc, char* args[]) {
    //file reading 
    if (argc != 2) {
        std::cerr << "incorrect number of arguments!! expected 1 but got " << argc - 1 << std::endl;
        return -1;
    }
    std::ifstream inputFile(args[1]);
    if (!inputFile) {
        std::cerr << "couldn't find file " << args[1] << std::endl;
        return -1;
    }
    if (processFile(std::ifstream(args[1])) == -1)
        return -1;

    //gets the safe state
    std::vector<int> safeState = getSafeState();
    //exits if it's not safe 
    if (safeState.empty()) {
        std::cout << "the system is not in a safe state!!" << std::endl;
        return 0;
    }
    //prints the safe sequence if it was safe
    else {
        std::cout << "<";
        for (size_t i = 0; i < safeState.size(); i++) {
            std::cout << "P" << safeState[i];
            if (i + 1 != safeState.size()) {
                std::cout << ", ";
            }
        }
        std::cout << ">" << std::endl;
    }
}

// sets up all the variables from the input file 
// this part took me significantly longer than the banker's algorithm did because I had to make splitString
int processFile(std::ifstream inputFile) {
    //processes the available resources 
    char temp[256];
    inputFile.getline(temp, 256);
    std::string tempStr(temp);
    std::vector<std::string> tempVec = splitString(tempStr, ',');
    for (size_t i = 0; i < tempVec.size(); i++) {
        availableResources.push_back(std::stoi(tempVec[i]));
    }

    //processes everything else 
    while (!inputFile.eof()) {
        inputFile.getline(temp, 256);
        tempStr = std::string(temp);
        std::vector<std::string> processInfo = splitString(tempStr, ' ');

        //max process resources
        std::vector<std::string> maxPR = splitString(processInfo[0], ',');
        std::vector<int> maxPR_int;
        for (size_t i = 0; i < maxPR.size(); i++) {
            maxPR_int.push_back(std::stoi(maxPR[i]));
        }
        maxProcessResources.push_back(maxPR_int);

        //allocated process resources
        std::vector<std::string> allocatedPR = splitString(processInfo[1], ',');
        std::vector<int> allocatedPR_int;
        for (size_t i = 0; i < allocatedPR.size(); i++) {
            allocatedPR_int.push_back(std::stoi(allocatedPR[i]));
        }
        allocatedProcessResources.push_back(allocatedPR_int);

        //needed process resources
        std::vector<int> neededPR;
        for (size_t i = 0; i < maxPR_int.size(); i++) {
            neededPR.push_back(maxPR_int[i] - allocatedPR_int[i]);
        }
        neededProcessResources.push_back(neededPR);
    }
    return 0;
}

// the actual banker's algorithm 
std::vector<int> getSafeState() {
    //the variable that ultimately gets returned 
    std::vector<int> safeState;
    //copy to not disrupt the original 
    std::vector<int> availableCopy = availableResources;
    //tracks which arrays have been allocated already 
    std::vector<bool> allocated;
    for (size_t i = 0; i < neededProcessResources.size(); i++) {
        allocated.push_back(false);
    }
    //algorithm starts
    while (hasFalseEntry(allocated)) {
        bool foundOne = false;
        for (size_t i = 0; i < neededProcessResources.size(); i++) {
            if (!allocated[i] && vectorLTE(neededProcessResources[i], availableCopy)) {
                foundOne = true;
                allocated[i] = true;
                for (size_t j = 0; j < neededProcessResources[i].size(); j++) {
                    availableCopy[j] += neededProcessResources[i][j];
                }
                safeState.push_back(i);
            }
        }
        if (!foundOne) {
            safeState.clear();
            return safeState;
        }
    }
    return safeState;
}

// apparently C++ is one of the few languages that doesn't have a string split function by default 
std::vector<std::string> splitString(std::string str, char splitter) {
    std::vector<std::string> substrings;
    size_t pos = 0;
    std::string tempStr = str;
    while ((pos = tempStr.find(splitter)) != std::string::npos) {
        std::string substr = tempStr.substr(0, pos);
        substrings.push_back(substr);
        tempStr.erase(0, pos + 1);
    }
    substrings.push_back(tempStr);
    return substrings;
}

bool hasFalseEntry(std::vector<bool> vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        if (!vec[i])
            return true;
    }
    return false;
}

// returns false if any entry in lhs is larger than its respective entry in rhs 
bool vectorLTE(std::vector<int> lhs, std::vector<int> rhs) {
    for (size_t i = 0; i < lhs.size(); i++) {
        if (lhs[i] > rhs[i])
            return false;
    }
    return true;
}