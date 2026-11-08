/*
 * CampusGraph.h
 * Purpose: Undirected graph of campus buildings and walkways.
 *          Stored as an adjacency list; supports BFS reachability.
 * Author: Nansu Baniya (Member B)
 */
#ifndef CAMPUSGRAPH_H
#define CAMPUSGRAPH_H

#include <string>
#include <vector>
#include <utility>
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

	void displayGraph() const; 
	int getDegree(int index) const;
	vector<pair<int, int>> bfs(int start) const;
	void displayCountsAndDegrees() const;
	void displayReachable(const string& startName) const;

	ConnectionResult addConnection(const string& nameA, const string& nameB);

private:
	vector<string>names_;
	vector<vector<int>> adjacency_;
	int connectionCount_=0;
	bool hasConnection(int a, int b) const;

};

#endif

