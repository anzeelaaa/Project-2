#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "Facility.h"
#include <vector>
#include <string>

using namespace std;

class HashTable {
private:
    vector<vector<Facility>> table;

    int capacity;
    int entries;
    int collisions;

    int hashFunction(const string& id) const;

public:
    HashTable(int size = 11);

    // Insert a facility
    bool insert(const Facility& facility);

    // Searche for a facility by ID
    const Facility* search(const string& id) const;

    // Returns hash table
    int getCapacity() const;
    int getEntries() const;
    int getCollisions() const;
};

#endif
