
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
    // Optional data directory argument (NFR-10)
    string dataDir = "data";

    if (argc > 1)
    {
        dataDir = argv[1];
    }

    if (!dataDir.empty() && dataDir.back() == '/')
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

    // Create and load department tree (Member C)
    DepartmentTree departmentTree;
    departmentTree.loadFromFile(dataDir + "/departments.txt");

    string choice;

    do
    {
        cout << "\n========== CAMPUS MANAGEMENT SYSTEM ==========" << endl;

        cout << "\nFACILITY MANAGEMENT" << endl;
        cout << "1. View all facilities" << endl;
        cout << "2. Search facility by ID" << endl;

        cout << "\nCAMPUS GRAPH" << endl;
        cout << "3. View campus graph" << endl;
        cout << "4. Display graph counts and degrees" << endl;
        cout << "5. Find reachable buildings" << endl;

        cout << "\nDEPARTMENT TREE (Member C)" << endl;
        cout << "9. Add department" << endl;
        cout << "10. Search department" << endl;
        cout << "11. Display department hierarchy" << endl;
        cout << "12. Display preorder traversal" << endl;
        cout << "13. Display postorder traversal" << endl;
        cout << "14. Display level-order traversal" << endl;
        cout << "15. Display department statistics" << endl;

        cout << "\n18. Exit" << endl;

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

        // Option 5: Find reachable buildings
        else if (choice == "5")
        {
            string startName;

            cout << "Enter starting building: ";
            getline(cin, startName);

            graph.displayReachable(startName);
        }

        // Option 9: Add department
        else if (choice == "9")
        {
            string departmentName;
            string parentName;

            cout << "Enter new department name: ";
            getline(cin, departmentName);

            if (departmentTree.isEmpty())
            {
                departmentTree.addDepartment(departmentName);
            }
            else
            {
                cout << "Enter parent department name: ";
                getline(cin, parentName);

                departmentTree.addDepartment(
                    departmentName,
                    parentName
                );
            }
        }

        // Option 10: Search department
        else if (choice == "10")
        {
            string departmentName;

            cout << "Enter department name to search: ";
            getline(cin, departmentName);

            departmentTree.searchDepartment(departmentName);
        }

        // Option 11: Display department hierarchy
        else if (choice == "11")
        {
            departmentTree.displayHierarchy();
        }

        // Option 12: Preorder traversal
        else if (choice == "12")
        {
            departmentTree.displayPreorder();
        }

        // Option 13: Postorder traversal
        else if (choice == "13")
        {
            departmentTree.displayPostorder();
        }

        // Option 14: Level-order traversal
        else if (choice == "14")
        {
            departmentTree.displayLevelOrder();
        }

        // Option 15: Department statistics
        else if (choice == "15")
        {
            departmentTree.displayStatistics();
        }

        // Option 18: Exit
        else if (choice == "18")
        {
            cout << "Exiting Campus Management System..." << endl;
        }

        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != "18");

    return 0;
}
