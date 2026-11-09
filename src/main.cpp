
#include <iostream>
#include <vector>
#include <string>

#include "../include/BuildingLoader.h"
#include "../include/FacilityLoader.h"
#include "../include/HashTable.h"
#include "../include/CampusGraph.h"
#include "../include/ConnectionLoader.h"
#include "../include/DepartmentTree.h"

using namespace std;

int main(int argc, char* argv[])
{
    // Optional data directory argument
    string dataDir = "data";

    if (argc > 1)
    {
        dataDir = argv[1];
    }

    // Remove trailing slash if present
    if (!dataDir.empty() &&
        (dataDir.back() == '/' || dataDir.back() == '\\'))
    {
        dataDir.pop_back();
    }

    // Load buildings
    vector<string> buildings =
        loadBuildings(dataDir + "/buildings.txt");

    // Build campus graph and load connections
    CampusGraph graph;

    for (const string& name : buildings)
    {
        graph.addBuilding(name);
    }

    loadConnections(dataDir + "/connections.txt", graph);

    // Create hash table
    HashTable facilities;

    vector<Facility> acceptedFacilities;

    // Load facilities
    loadFacilities(
        dataDir + "/facilities.txt",
        buildings,
        facilities,
        acceptedFacilities
    );

    // Load department tree
    DepartmentTree departmentTree;

    departmentTree.loadFromFile(dataDir + "/departments.txt");

    string choice;

    do
    {
        cout << "\nCAMPUS MANAGEMENT SYSTEM\n" << endl;

        cout << "FACILITY MANAGEMENT" << endl;
        cout << "1. View all facilities" << endl;
        cout << "2. Search facility by ID" << endl;

        cout << "\nCAMPUS GRAPH" << endl;
        cout << "3. View campus graph" << endl;
        cout << "4. Display graph counts and degrees" << endl;
        cout << "5. Find reachable buildings (BFS)" << endl;

        cout << "\nDEPARTMENT TREE" << endl;
        cout << "6. Add department" << endl;
        cout << "7. Search department" << endl;
        cout << "8. Display department hierarchy" << endl;
        cout << "9. Run preorder traversal" << endl;

        cout << "10. Exit" << endl;
        cout << "\nEnter your choice: ";

        getline(cin, choice);

        // Option 1: View all facilities
        if (choice == "1")
        {
            cout << "\nAll Facilities:" << endl;

            for (const Facility& facility : acceptedFacilities)
            {
                facility.display();
            }

            cout << "Total Facilities: "
                 << acceptedFacilities.size() << endl;
        }

        // Option 2: Search facility by ID
        else if (choice == "2")
        {
            string userID;

            cout << "Enter facility ID: ";
            getline(cin, userID);

            userID = normalizeFacilityID(userID);

            if (!isValidFacilityID(userID))
            {
                cout << "Invalid facility ID format." << endl;
            }
            else
            {
                const Facility* result = facilities.search(userID);

                if (result != nullptr)
                {
                    cout << "\nFacility found!" << endl;
                    result->display();
                }
                else
                {
                    cout << "Facility " << userID
                         << " was not found." << endl;
                }
            }
        }

        // Option 3: View campus graph
        else if (choice == "3")
        {
            graph.displayGraph();
        }

        // Option 4: Display graph counts and degrees
        else if (choice == "4")
        {
            graph.displayCountsAndDegrees();
        }

        // Option 5: Find reachable buildings using BFS
        else if (choice == "5")
        {
            string startName;

            cout << "Enter starting building: ";
            getline(cin, startName);

            graph.displayReachable(startName);
        }

        // Option 6: Add department
        else if (choice == "6")
        {
            string departmentName;
            string parentName;

            cout << "Enter department name: ";
            getline(cin, departmentName);

            if (!departmentTree.isEmpty())
            {
                cout << "Enter parent department: ";
                getline(cin, parentName);
            }

            if (departmentTree.addDepartment(
                    departmentName, parentName))
            {
                cout << "Department added successfully." << endl;
            }
            else
            {
                cout << "Could not add department." << endl;
            }
        }

        // Option 7: Search department
        else if (choice == "7")
        {
            string departmentName;

            cout << "Enter department name to search: ";
            getline(cin, departmentName);

            departmentTree.searchDepartment(departmentName);
        }

        // Option 8: Display department hierarchy
        else if (choice == "8")
        {
            departmentTree.displayHierarchy();
        }

        // Option 9: Run preorder traversal
        else if (choice == "9")
        {
            departmentTree.displayPreorder();
        }

        // Option 10: Exit
        else if (choice == "10")
        {
            cout << "Exiting Campus Management System." << endl;
        }

        // Invalid menu choice
        else
        {
            cout << "Invalid choice. Please enter a number from 1 to 10."
                 << endl;
        }

    } while (choice != "10");

    return 0;
}
