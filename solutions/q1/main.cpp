#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <regex>
#include <filesystem>
#include <deque>
#include <algorithm>
#include "filter.h"

namespace fs = std::filesystem;

// Number of recent readings each altimeter's median is computed over.
constexpr size_t WINDOW_SIZE = 125;

// Median of a window's current contents (uses whatever is available if not yet full).
double median(const std::deque<double>& window) {
    std::vector<double> sorted(window.begin(), window.end());
    std::sort(sorted.begin(), sorted.end());
    size_t n = sorted.size();
    if (n % 2 == 0) {
        return (sorted[n / 2 - 1] + sorted[n / 2]) / 2.0;
    }
    return sorted[n / 2];
}

// Pushes a value into a sliding window, evicting the oldest once over windowSize.
void pushToWindow(std::deque<double>& window, double value, size_t windowSize) {
    window.push_back(value);
    if (window.size() > windowSize) {
        window.pop_front();
    }
}

// Reads one logX.csv file, applies the filter, and writes correctedX.csv
void processFile(const fs::path& inPath, const fs::path& outPath, size_t windowSize) {
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

    Filter f(0.95);
    std::deque<double> a1Window;
    std::deque<double> a2Window;
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
        double a2 = values.at(2);

        pushToWindow(a1Window, a1, windowSize);
        pushToWindow(a2Window, a2, windowSize);
        double avgAlt = (median(a1Window) + median(a2Window)) / 2.0;

        double filtered = f.correct(gps - avgAlt);
        double altitude = gps - filtered;
        if (altitude < 0) {
            altitude = 0;
        }

        outputFile << altitude << std::endl;
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
            processFile(entry.path(), outPath, WINDOW_SIZE);
            std::cout << "Processed " << filename << " -> " << outPath.filename().string() << std::endl;
        }
    }

    std::cout << "Done." << std::endl;
    return 0;
}
