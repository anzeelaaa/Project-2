#ifndef FACILITY_H
#define FACILITY_H

#include <string>
using namespace std;

class Facility {
private:
    string facilityID;
    string facilityName;
    string buildingName;
    string category;

public:
    Facility();

    Facility(const string& id,
             const string& name,
             const string& building,
             const string& cat);

    string getID() const;
    string getName() const;
    string getBuilding() const;
    string getCategory() const;

    void display() const;
};

bool isValidFacilityID(const string& id);
string normalizeFacilityID(const string& id);
string normalizeText(const string& text);

#endif
