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
        cout << "3. Search facility by name" << endl;
        cout << "4. Search facilities by category" << endl;
        cout << "5. Display category report" << endl;

        cout << "\nCAMPUS GRAPH" << endl;
        cout << "6. View campus graph" << endl;
        cout << "7. Display graph counts and degrees" << endl;
        cout << "8. Find reachable buildings (BFS)" << endl;

        cout << "\nDEPARTMENT TREE" << endl;
        cout << "9. Add department" << endl;
        cout << "10. Search department" << endl;
        cout << "11. Display department hierarchy" << endl;
        cout << "12. Run preorder traversal" << endl;

        cout << "13. Exit" << endl;
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

        // Option 3: Search facility by name
        else if (choice == "3")
        {
            string searchName;
            bool found = false;

            cout << "Enter facility name: ";
            getline(cin, searchName);

            for (const Facility &facility : acceptedFacilities)
            {
                if (normalizeText(facility.getName()) ==
                    normalizeText(searchName))
                {
                    facility.display();
                    found = true;
                }
            }

            if (!found)
            {
                cout << "No facilities found with that name." << endl;
            }
        }

        // Option 4: Search facilities by category
        else if (choice == "4")
        {
            string searchCategory;
            bool found = false;

            cout << "Enter facility category: ";
            getline(cin, searchCategory);

            for (const Facility &facility : acceptedFacilities)
            {
                if (normalizeText(facility.getCategory()) ==
                    normalizeText(searchCategory))
                {
                    facility.display();
                    found = true;
                }
            }

            if (!found)
            {
                cout << "No facilities found in that category." << endl;
            }
        }

        // Option 5: Display category report
        else if (choice == "5")
        {
            vector<string> categories;

            for (const Facility &facility : acceptedFacilities)
            {
                string category = normalizeText(facility.getCategory());

                bool alreadyExists = false;

                for (const string &existing : categories)
                {
                    if (existing == category)
                    {
                        alreadyExists = true;
                        break;
                    }
                }

                if (!alreadyExists)
                {
                    categories.push_back(category);
                }
            }

            cout << "\nFACILITY CATEGORY REPORT" << endl;

            for (const string &category : categories)
            {
                int count = 0;

                cout << "\nCategory: " << category << endl;

                for (const Facility &facility : acceptedFacilities)
                {
                    if (normalizeText(facility.getCategory()) == category)
                    {
                        facility.display();
                        count++;
                    }
                }

                cout << "Total in category: " << count << endl;
            }

            cout << "\nTotal Facilities: "
                 << acceptedFacilities.size() << endl;
        }

        // Option 6: View campus graph
        else if (choice == "6")
        {
            graph.displayGraph();
        }

        // Option 7: Display graph counts and degrees
        else if (choice == "7")
        {
            graph.displayCountsAndDegrees();
        }

        // Option 8: Find reachable buildings using BFS
        else if (choice == "8")
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

        // Option 12: Run preorder traversal
        else if (choice == "12")
        {
            departmentTree.displayPreorder();
        }

        // Option 13: Exit
        else if (choice == "12")
        {
            cout << "Exiting Campus Management System." << endl;
        }

        // Invalid menu choice
        else
        {
            cout << "Invalid choice. Please enter a number from 1 to 13."
                 << endl;
        }

    } while (choice != "13");

    return 0;
}
