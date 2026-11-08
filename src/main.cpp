#include <iostream>
#include <vector>
#include <string>
#include "../include/BuildingLoader.h"
#include "../include/FacilityLoader.h"
#include "../include/HashTable.h"
#include "../include/CampusGraph.h"
#include "../include/ConnectionLoader.h"
using namespace std;

int main()
{
  // Load buildings
  vector<string> buildings = loadBuildings("data/buildings.txt");

  // build campus graph then load connections 
  CampusGraph graph;
  for (const string& name: buildings){
	graph.addBuilding(name);
  }
  loadConnections("data/connections.txt", graph);

  // Create hash table
  HashTable facilities;

  vector<Facility> acceptedFacilities;

  // Load facilities
  loadFacilities(
      "data/facilities.txt",
      buildings,
      facilities,
      acceptedFacilities);

  string choice;

  do
  {
    cout << "\n FACILITY MANAGEMENT: " << endl;
    cout << "1. View all facilities" << endl;
    cout << "2. Search facility by ID" << endl;
    cout << "3. View campus graph" <<endl;
    cout << "4. display graph counts and degrees" <<endl;
    cout << "5. find reachable buildings " <<endl;
    cout << "10. Exit" << endl;
    cout << "Enter your choice: ";

    getline(cin, choice);

    if (choice == "1")
    {
      cout << "\nAll Facilities: " << endl;

      for (const Facility &facility : acceptedFacilities)
      {
        facility.display();
      }

      cout << "Total Facilities: "
           << acceptedFacilities.size() << endl;
    }

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
        const Facility *result = facilities.search(userID);

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
 
    else if (choice == "3"){
	graph.displayGraph();
    }
    else if (choice =="4"){
		graph.displayCountsAndDegrees();
    }
    else if ( choice == "5"){
	string startName;
	cout<< "enter starting building: ";
	getline(cin, startName);
	graph.displayReachable(startName);
    }


    else if (choice == "10")
    {
      cout << " " << endl;
    }


  } while (choice != "10");

  return 0;
}
