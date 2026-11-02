#include "../include/HashTable.h"
using namespace std;

HashTable::HashTable(int size) {
    if (size <= 0) {
        size = 11;
    }

    capacity = size;
    entries = 0;
    collisions = 0;

    table.resize(capacity);
}

int HashTable::hashFunction(const string& id) const {
    unsigned long long hashValue = 0;

    for (char c : id) {
        hashValue = (hashValue * 31 +
                     static_cast<unsigned char>(c)) % capacity;
    }

    return static_cast<int>(hashValue);
}

// Insert a facility into hash table
bool HashTable::insert(const Facility& facility) {
    string id = normalizeFacilityID(facility.getID());

    // Reject invalid IDs
    if (!isValidFacilityID(id)) {
        return false;
    }

    int index = hashFunction(id);

    // Check for duplicate IDs
    for (const Facility& existing : table[index]) {
        if (existing.getID() == id) {
            return false;
        }
    }

    // Count collision if bucket already contains facility
    if (!table[index].empty()) {
        collisions++;
    }

    // Store the facility with ID
    Facility newFacility(
        id,
        facility.getName(),
        facility.getBuilding(),
        facility.getCategory()
    );

    table[index].push_back(newFacility);
    entries++;

    return true;
}

// Search for a facility using  ID
const Facility* HashTable::search(const string& id) const {
    string normalizedID = normalizeFacilityID(id);

    if (!isValidFacilityID(normalizedID)) {
        return nullptr;
    }

    int index = hashFunction(normalizedID);

    for (const Facility& facility : table[index]) {
        if (facility.getID() == normalizedID) {
            return &facility;
        }
    }

    return nullptr;
}

// Returns table capacity
int HashTable::getCapacity() const {
    return capacity;
}

// Returns the number of stored facilities
int HashTable::getEntries() const {
    return entries;
}

// Returns the number of collisions
int HashTable::getCollisions() const {
    return collisions;
}
