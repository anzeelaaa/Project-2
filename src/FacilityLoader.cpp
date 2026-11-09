/*
 * FacilityLoader.cpp
 * Purpose: Loads facility records from file, validates,inserts valid facilities into
   the hash table
 * Author: Anzeela Mahmood (Member A)
 */

#include "../include/FacilityLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// Remove whitespace 
string trimField(const string& text) {
    size_t start = text.find_first_not_of(" \t\n\r");

    if (start == string::npos) {
        return "";
    }

    size_t end = text.find_last_not_of(" \t\n\r");

    return text.substr(start, end - start + 1);
}

string findBuildingName(const string& name,
                        const vector<string>& buildingNames) {
    for (const string& building : buildingNames) {
        if (normalizeText(building) == normalizeText(name)) {
            return building;
        }
    }

    return "";
}

// Loads facilities from file
FacilityLoadStats loadFacilities(
    const string &filename,
    const vector<string> &buildingNames,
    HashTable &facilities,
    vector<Facility> &acceptedFacilities)
{

    FacilityLoadStats stats = {0, 0};

    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cout << "Error: Could not open " << filename << endl;
        return stats;
    }

    string line;
    int lineNumber = 0;

    while (getline(inputFile, line)) {
        lineNumber++;

        if (trimField(line).empty()) {
            continue;
        }

        size_t firstCharacter = line.find_first_not_of(" \t\r");

        if (firstCharacter != string::npos &&
            line[firstCharacter] == '#') {
            continue;
        }

        vector<string> fields;
        string field;
        stringstream lineStream(line);

        while (getline(lineStream, field, '|')) {
            fields.push_back(trimField(field));
        }

        if (fields.size() != 4) {
            cout << "Warning: " << filename
                 << ", line " << lineNumber
                 << ": Expected exactly 4 fields." << endl;

            stats.rejected++;
            continue;
        }

        string id = normalizeFacilityID(fields[0]);
        string name = fields[1];
        string building = fields[2];
        string category = fields[3];

        // Validate facility ID
        if (!isValidFacilityID(id)) {
            cout << "Warning: " << filename
                 << ", line " << lineNumber
                 << ": Invalid facility ID." << endl;

            stats.rejected++;
            continue;
        }

        // Validate facility name
        if (name.empty()) {
            cout << "Warning: " << filename
                 << ", line " << lineNumber
                 << ": Facility name cannot be empty." << endl;

            stats.rejected++;
            continue;
        }

        // Validate category
        if (category.empty()) {
            cout << "Warning: " << filename
                 << ", line " << lineNumber
                 << ": Category cannot be empty." << endl;

            stats.rejected++;
            continue;
        }

        // Check whether building exists
        string correctBuildingName =
            findBuildingName(building, buildingNames);

        if (correctBuildingName.empty()) {
            cout << "Warning: " << filename
                 << ", line " << lineNumber
                 << ": Building does not exist." << endl;

            stats.rejected++;
            continue;
        }

        // Create facility and insert into hash table
        Facility facility(id, name, correctBuildingName, category);

        if (!facilities.insert(facility)) {
            cout << "Warning: " << filename
                 << ", line " << lineNumber
                 << ": Duplicate facility ID." << endl;

            stats.rejected++;
            continue;
        }

        acceptedFacilities.push_back(facility);
        stats.accepted++;
    }

    inputFile.close();

    // Display summary
    cout << "\nFacility Loading Summary" << endl;
    cout << "Accepted: " << stats.accepted << endl;
    cout << "Rejected: " << stats.rejected << endl;
    cout << "Hash Table Capacity: " << facilities.getCapacity() << endl;
    cout << "Hash Table Entries: " << facilities.getEntries() << endl;
    cout << "Hash Table Collisions: " << facilities.getCollisions() << endl;

    return stats;
}