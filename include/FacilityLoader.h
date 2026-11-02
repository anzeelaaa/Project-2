#ifndef FACILITYLOADER_H
#define FACILITYLOADER_H
#include "Facility.h"
#include "HashTable.h"
#include <string>
#include <vector>
using namespace std;

struct FacilityLoadStats {
    int accepted;
    int rejected;
};

FacilityLoadStats loadFacilities(
    const string &filename,
    const vector<string> &buildingNames,
    HashTable &facilities,
    vector<Facility> &acceptedFacilities);

#endif