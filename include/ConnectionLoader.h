/*
 * ConnectionLoader.h
 * Purpose: Loads connections.txt into the campus graph, rejecting
 *          bad records with warnings and printing a load summary.
 * Author: Nansu Baniya (Member B)
 */
#ifndef CONNECTION_H
#define CONNECTION_H

#include "CampusGraph.h"
#include <string>
using namespace std;

struct ConnectionLoadStats {
	int accepted;
	int rejected;
};

ConnectionLoadStats loadConnections (const string& filename, CampusGraph& graph);

#endif



