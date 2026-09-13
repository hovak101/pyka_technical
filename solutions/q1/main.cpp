#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <regex>
#include <filesystem>
#include "filter.h"

namespace fs = std::filesystem;

// Reads one logX.csv file, applies the filter, and writes correctedX.csv
void processFile(const fs::path& inPath, const fs::path& outPath) {
    std::ifstream inputFile(inPath);
    std::ofstream outputFile(outPath);

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input file " << inPath << std::endl;
        return;
    }
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open output file " << outPath << std::endl;
        return;
    }

    Filter f(0.9);
    outputFile << "altitude_estimate" << std::endl;

    std::string line;
    std::getline(inputFile, line); // skip header

    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<double> values;

        std::getline(ss, cell, ','); // skip timestamp
        while (std::getline(ss, cell, ',')) {
            values.push_back(std::stod(cell));
        }
        double gps = values.at(0);
        double a1 = values.at(1);

        outputFile << gps - f.correct(gps - a1) << std::endl;
    }
}

int main() {
    fs::path data_dir = fs::path(PROJECT_SOURCE_DIR) / "data";
    fs::path output_dir = fs::path(PROJECT_SOURCE_DIR) / "output";

    fs::create_directories(output_dir);

    std::regex log_pattern(R"(log(\d+)\.csv)");

    for (const auto& entry : fs::directory_iterator(data_dir)) {
        std::string filename = entry.path().filename().string();
        std::smatch match;
        if (entry.is_regular_file() && std::regex_match(filename, match, log_pattern)) {
            std::string x = match[1];
            fs::path outPath = output_dir / ("corrected" + x + ".csv");
            processFile(entry.path(), outPath);
            std::cout << "Processed " << filename << " -> " << outPath.filename().string() << std::endl;
        }
    }

    std::cout << "Done." << std::endl;
    return 0;
}
