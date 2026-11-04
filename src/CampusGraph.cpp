/*
 * CampusGraph.cpp
 * Purpose: Implementation of the campus graph.
 * Author: Nansu Baniya (Member B)
 */
#include "../include/CampusGraph.h"
#include <cctype>

static bool isSpaceChar(char c){
	return c== ' '|| c=='\t' ||c=='\r' || c=='\n';
}

//removes white space 

static string trimText (const string& s){
	size_t start=0;
	while ((start<s.size()) && isSpaceChar(s[start])) start++;
	size_t end=s.size();
	while (end> start && isSpaceChar(s[end-1])) end--;
	return s.substr(start,end - start);
}

//returns lowercase copy 

static string lowerText( string s ){
	for (char& c : s) c= static_cast<char>(tolower(static_cast<unsigned char>(c)));
	return s;
}

//returns building index 

int CampusGraph :: findBuilding(const string& name) const{
	string target= lowerText(trimText(name));
	for (int i=0; i<static_cast<int>(names_.size()); i++){
		if (lowerText(names_[i]) == target)
			return i; 
	}
	return -1;
}


//adding new building 

bool CampusGraph:: addBuilding(const string& name){
	string clean= trimText(name);
	if (clean.empty()) return false;
	if (findBuilding(clean) !=-1) return false;
	names_.push_back(clean);
	adjacency_.push_back(vector<int>());
	return true;
}

//checking neighbours
bool CampusGraph:: hasConnection(int a, int b) const{
	for (int neighbor : adjacency_[a]) {
		if (neighbor== b) return true;
	}
	return false;
}

 
ConnectionResult CampusGraph :: addConnection(const string& nameA, const string& nameB){
	int a = findBuilding(nameA);
	if (a==-1) return CONNECTION_UNKNOWN_FIRST;
	int b= findBuilding(nameB);
	if(b==-1) return CONNECTION_UNKNOWN_SECOND;
	if(a==b) return CONNECTION_SELF;
	if (hasConnection(a,b)) return CONNECTION_DUPLICATE;

	adjacency_[a].push_back(b);
	adjacency_[b].push_back(a);
	connectionCount_++;
	return CONNECTION_ADDED;
}


