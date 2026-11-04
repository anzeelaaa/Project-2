#ifndef CAMPUSGRAPH_H
#define CAMPUSGRAPH_H

#include <string>
#include <vector>
using namespace std;

enum ConnectionResult{
	CONNECTION_ADDED,
	CONNECTION_UNKNOWN_FIRST,
	CONNECTION_UNKNOWN_SECOND,
	CONNECTION_SELF,
	CONNECTION_DUPLICATE,
};


class CampusGraph{
public:
	int findBuilding(const string& name) const;

	bool addBuilding(const string& name);

	ConnectionResult addConnection(const string& nameA, const string& nameB);

private:
	vector<string>names_;
	vector<vector<int>> adjacency_;
	int connectionCount_=0;
	bool hasConnection(int a, int b) const;

};

#endif

