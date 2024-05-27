#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <chrono>

std::string findUniqueSubstring(const std::string& input) {
    std::unordered_map<char, int> countMap;
    int maxUniqueCount = 0;
    std::string maxUniqueSubstring;

    for (int i = 0; i < input.length(); ++i) {
        countMap.clear();

        for (int j = i; j < input.length(); ++j) {
            countMap[input[j]]++;

            if (countMap[input[j]] > 1) {
                break;
            }

            int uniqueCount = std::count_if(countMap.begin(), countMap.end(),
                [](const std::pair<char, int>& pair) { return pair.second == 1; });

            if (uniqueCount > maxUniqueCount) {
                maxUniqueCount = uniqueCount;
                maxUniqueSubstring = input.substr(i, j - i + 1);
            }
            else if (uniqueCount == maxUniqueCount && input.substr(i, j - i + 1) < maxUniqueSubstring) {
                maxUniqueSubstring = input.substr(i, j - i + 1);
            }
        }
    }

    return maxUniqueSubstring;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Invalid arguments count\n"
            << "Usage: copyfile.exe <input file> <output file>\n";
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    std::ofstream outputFile(argv[2]);

    int length;
    std::string inputString;

    if (inputFile.is_open()) {
        inputFile >> length;
        inputFile >> inputString;
        inputFile.close();

        auto startTime = std::chrono::high_resolution_clock::now();

        std::string result = findUniqueSubstring(inputString);

        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

        std::cout << "Result: " << result << std::endl;
        std::cout << "Execution time: " << duration.count() << " ms" << std::endl;

        if (outputFile.is_open()) {
            outputFile << result;
            outputFile.close();
        }
        else {
            std::cout << "Unable to open the output file." << std::endl;
            return 1;
        }
    }
    else {
        std::cout << "Unable to open the input file." << std::endl;
        return 1;
    }

    return 0;
}
