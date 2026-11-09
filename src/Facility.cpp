/*
 * Facility.cpp
 * Purpose: Implements facility class,
  including facility information, display, and ID/text validation.
 * Author: Anzeela Mahmood (Member A)
 */
#include "../include/Facility.h"
#include <iostream>
#include <cctype>
using namespace std;

Facility::Facility() {
    facilityID = "";
    facilityName = "";
    buildingName = "";
    category = "";
}

Facility::Facility(const string& id,
                   const string& name,
                   const string& building,
                   const string& cat) {
    facilityID = normalizeFacilityID(id);
    facilityName = name;
    buildingName = building;
    category = cat;
}

string Facility::getID() const {
    return facilityID;
}

string Facility::getName() const {
    return facilityName;
}

string Facility::getBuilding() const {
    return buildingName;
}

string Facility::getCategory() const {
    return category;
}

void Facility::display() const {
    cout << "Facility ID: " << facilityID << endl;
    cout << "Facility Name: " << facilityName << endl;
    cout << "Building: " << buildingName << endl;
    cout << "Category: " << category << endl;
}

bool isValidFacilityID(const string& id) {
    if (id.length() != 4 || toupper(static_cast<unsigned char>(id[0])) != 'F') {
        return false;
    }

    for (int i = 1; i < 4; i++) {
        if (!isdigit(static_cast<unsigned char>(id[i]))) {
            return false;
        }
    }

    return true;
}

string normalizeFacilityID(const string& id) {
    string result = id;

    size_t start = result.find_first_not_of(" \t\n\r");
    if (start == string::npos) {
        return "";
    }

    size_t end = result.find_last_not_of(" \t\n\r");
    result = result.substr(start, end - start + 1);

    for (char& c : result) {
        c = static_cast<char>(toupper(static_cast<unsigned char>(c)));
    }

    return result;
}

// gets rid of whitespace and converts text to lowercase
string normalizeText(const string& text) {
    size_t start = text.find_first_not_of(" \t\n\r");

    if (start == string::npos) {
        return "";
    }

    size_t end = text.find_last_not_of(" \t\n\r");
    string result = text.substr(start, end - start + 1);

    for (char& c : result) {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }

    return result;
}
