#include "../include/ConnectionLoader.h"
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

// removing space, tabs ,\r and \n 
static string trimConnectionField (const string& s){
	size_t start=s.find_first_not_of(" \t\r\n");
	if (start == string::npos) return "";
	size_t end=s.find_last_not_of(" \t\r\n");
	return s.substr(start, end - start +1);
}

// spliting a line on '|' and trims each pieces 

static vector <string> splitConnectionLine (const string& line){
	vector <string> fields;
	string current;
	for (char c:line){
			if(c== '|'){
				fields.push_back(trimConnectionField(current));
				current="";
			}
			else{
				current +=c;
			}
		}
	fields.push_back(trimConnectionField(current));
	return fields;
}

// print rejection warning 

static void warnConnection(const string& filename, int lineNumber, const string& reason){
	cout<<"warning: "<<filename<<", line number "<<lineNumber<<": "<<reason<<endl;
}

//prints summary 

static void printConnectionSummary (const ConnectionLoadStats& stats){
	cout<<"\nConnection Loading Summary"<<endl;
	cout<<"Accepted: "<<stats.accepted<<endl;
	cout<<"rejected: "<<stats.rejected<<endl;
}

//check order 

ConnectionLoadStats loadConnections(const string& filename, CampusGraph& graph){
	ConnectionLoadStats stats={0,0};
	ifstream inputFile(filename);
	if (!inputFile.is_open()){
		cout<<"error:could not open"<<filename<<"; treat it as empty"<<endl;
		printConnectionSummary(stats);
		return stats;
	}



	string line;
	int lineNumber=0;

	while (getline(inputFile, line)){
		lineNumber++;

		string trimmed=trimConnectionField(line);
		if (trimmed.empty()) continue;
		if (trimmed[0]=='#') continue;

		vector<string> fields=splitConnectionLine(line);

		if(fields.size() !=2){

			warnConnection(filename, lineNumber, "expected eaxctly 2 fields");
			stats.rejected++;
			continue;
		}

		if (fields[0].empty() || fields[1].empty()){
			warnConnection(filename, lineNumber, "Building name is empty");
			stats.rejected++;
			continue;
		}

		ConnectionResult result=graph.addConnection(fields[0], fields[1]);

		switch (result){
			case CONNECTION_ADDED:
				stats.accepted++;
				break;

			case CONNECTION_UNKNOWN_FIRST:
				warnConnection(filename, lineNumber, "unknown building\"" + fields[0] + "\".");
               			stats.rejected++;
               			break;
            		case CONNECTION_UNKNOWN_SECOND:
                		warnConnection(filename, lineNumber, "Unknown building \"" + fields[1] + "\".");
                		stats.rejected++;
                		break;
            		case CONNECTION_SELF:
                		warnConnection(filename, lineNumber, "A building cannot connect to itself.");
                		stats.rejected++;
                		break;
            		case CONNECTION_DUPLICATE:
                		warnConnection(filename, lineNumber, "Duplicate connection (possibly reversed).");
                		stats.rejected++;
                		break;
       		 }
    	}

    inputFile.close();
    printConnectionSummary(stats);
    return stats;
}

