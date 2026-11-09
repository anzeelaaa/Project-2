/*
 * BuildingLoader.cpp
 * Purpose: Loads building names from a file and checks for duplicate entries
 * Author: Anzeela Mahmood (Member A)
 */

#include "../include/BuildingLoader.h"
#include <iostream>
#include <fstream>
using namespace std;

// Remove whitespace
string trimBuildingName(const string& name) {
    size_t start = name.find_first_not_of(" \t\n\r");

    if (start == string::npos) {
        return "";
    }

    size_t end = name.find_last_not_of(" \t\n\r");

    return name.substr(start, end - start + 1);
}

//Load building names from file
vector<string> loadBuildings(const string& filename) {
    vector<string> buildings;
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cout << "Error: Could not open " << filename << endl;
        return buildings;
    }

    string line;
    int lineNumber = 0;
    int rejected = 0;

    while (getline(inputFile, line)) {
        lineNumber++;

        string buildingName = trimBuildingName(line);

        if (buildingName.empty()) {
            continue;
        }

        if (buildingName[0] == '#') {
            continue;
        }

        bool duplicate = false;

        for (const string& building : buildings) {
            string first = building;
            string second = buildingName;

            for (char& c : first) {
                c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
            }

            for (char& c : second) {
                c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
            }

            if (first == second) {
                duplicate = true;
                break;
            }
        }

        if (duplicate) {
            cout << "Warning: " << filename
                 << ", line " << lineNumber
                 << ": Duplicate building name." << endl;

            rejected++;
            continue;
        }

        buildings.push_back(buildingName);
    }

    inputFile.close();

    cout << "\nBuilding Loading Summary" << endl;
    cout << "Accepted: " << buildings.size() << endl;
    cout << "Rejected: " << rejected << endl;

    return buildings;
}