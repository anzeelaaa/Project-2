Smart Campus Navigation and Facility Management System
CSCE 2100 - Project 2

DESCRIPTION
Project 2 is a C++ menu program that helps users find campus facilities and
navigate between campus buildings. It loads buildings, walkway connections,
facilities, and departments from text files, rejects invalid records with
warnings, and prints a load summary for each file.

FEATURES
- View all facilities in file order with the total count
- Search for a facility by ID using a custom hash table 
- Detect and report hash table collisions 
- View the campus graph: each building and its connected buildings
- Display total buildings, total connections, and each building's degree
- Find all buildings reachable from a starting building using BFS, with distances
- Reject invalid records (wrong field count, empty fields, duplicates,
  unknown buildings) with warnings showing the file name, line number, and reason

BUILD
From the project root directory:
    g++ -std=c++17 -Wall -Wextra src/*.cpp -o campus

RUN
Using the default data directory (data/):
    ./campus
Using a different data directory (optional argument):
    ./campus testdata/<folder>
The folder should contain buildings.txt, connections.txt, facilities.txt,
and departments.txt. A missing file is reported and treated as empty.

DIRECTORY LAYOUT
    include/              header files
                          BuildingLoader.h, Facility.h, FacilityLoader.h,
                          HashTable.h, CampusGraph.h, ConnectionLoader.h
    src/                  source files
                          main.cpp, BuildingLoader.cpp, Facility.cpp,
                          FacilityLoader.cpp, HashTable.cpp,
                          CampusGraph.cpp, ConnectionLoader.cpp
    data/                 sample input files
                          buildings.txt, connections.txt,
                          facilities.txt, departments.txt
    testdata/             team test data
    README.txt            this file
    design_document.txt   hash function, collision strategy,
                          graph representation, main classes
    test_results.txt      recorded tests and results
    CONTRIBUTIONS.txt     team member contributions
    .gitignore            excludes the executable and editor files

TEAM MEMBERS

1. Nansu Baniya (username = nansubaniya22-sudo) - Member B: campus graph and BFS
2. Adebukola Adeyemi ( username = buki8222-alt) - Member C: department tree, traversals, department statistics
3. Anzeela Mahmood (username = anzeelaaa) - Member A: facility records, custom hash table, ID search, name and category search, category report

