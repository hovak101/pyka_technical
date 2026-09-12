#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "filter.h"

int main() {
    // initialize filter
    Filter f(0.5);
   
    // read csv row by row, simulating realtime environment
    std::string data_path = std::string(PROJECT_SOURCE_DIR) + "/data";
    std::ifstream inputFile(data_path + "/log1.csv");
    std::ofstream outputFile(data_path + "/corrected1.csv");

    // Check if the files opened successfully
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open the input file." << std::endl;
        return 1;
    }

    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open the output file." << std::endl;
        return 1;
    }

    outputFile << "altitude_estimate" << std::endl;

    std::string line;
    double gps;
    double a1;
    double a2;

    std::getline(inputFile, line);

    // Read the file line by line
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<double> values;

        // 3. Split the line using the comma (',') delimiter
        std::getline(ss, cell, ',');
        while (std::getline(ss, cell, ',')) {
            values.push_back(std::stod(cell));
        }
        gps = values.at(0);
        a1 = values.at(1);
        a2 = values.at(2);

        outputFile << gps - f.correct(gps - a1) << std::endl;
        std::cout << gps << " " << a1 << " " << a2 << std::endl;
    }

    // Close the file streams
    inputFile.close();
    outputFile.close();
    return 0;
}
