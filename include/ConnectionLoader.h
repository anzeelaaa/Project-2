#ifndef CONNECTION_H
#define Connection_h

#include "CampusGraph.h"
#include <string>
using namespace std;

struct ConnectionLoadStats {
	int accepted;
	int rejected;
};

ConnectionLoadStats loadConnections (const string& filename, CampusGraph& graph);

#endif



