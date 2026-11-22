/*
 * CampusGraph.cpp
 * Purpose: Implementation of the campus graph.
 * Author: Nansu Baniya (Member B)
 */
#include "../include/CampusGraph.h"
#include <cctype>
#include <iostream>
#include <queue>
#include <algorithm>

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

//return number of neighbor a building has
int CampusGraph::getDegree(int index) const {
	return static_cast<int>(adjacency_[index].size());
}

//menu option 3

void CampusGraph::displayGraph() const{
	if (names_.empty()){
		cout<<"no building are loaded"<<endl;
		return;
	}
	cout<<"\nCampus Graph: "<<endl;
	for (int i=0; i<static_cast<int>(names_.size()); i++){
		cout<<names_[i]<<" : ";
		if (adjacency_[i].empty()){
			cout<<"(no connection)";
		}
		else{
			for (size_t k=0; k<adjacency_[i].size(); k++){
				if (k>0) cout<<", ";
				cout<<names_[adjacency_[i][k]];
			}
		}
		cout<<endl;
	}
}
//menu option 4

void CampusGraph::displayCountsAndDegrees() const {
	cout << "\nTotal buildings: " << names_.size() << endl;
	cout << "Total connections: " << connectionCount_ << endl;
	if (names_.empty()) {
		cout << "No buildings are loaded." << endl;
		return;
	}
	cout << "Degrees:" << endl;
	for (int i = 0; i < static_cast<int>(names_.size()); i++) {
		cout << "  " << names_[i] << ": " << getDegree(i) << endl;
	}
}

//BFS from start 
vector<pair<int, int>> CampusGraph::bfs(int start) const {
	vector<pair<int, int>> order;
	vector<bool> visited(names_.size(), false);
	vector<int> distance(names_.size(), 0);
	queue<int> q;

	visited[start] = true;
	distance[start] = 0;
	q.push(start);

	while (!q.empty()) {
		int current = q.front();
		q.pop();
		order.push_back(make_pair(current, distance[current]));

		for (int next : adjacency_[current]) {
			if (!visited[next]) {
				visited[next] = true;
				distance[next] = distance[current] + 1;
				q.push(next);
			}
		}
	}
	return order;
}

//menu option 5 

void CampusGraph::displayReachable(const string& startName) const {
	string clean = trimText(startName);
	if (clean.empty()) {
		cout << "Error: building name cannot be blank." << endl;
		return;
	}
	int start = findBuilding(clean);
	if (start == -1) {
		cout << "Error: building \"" << clean << "\" was not found." << endl;
		return;
	}

	vector<pair<int, int>> order = bfs(start);
	cout << "\nFrom " << names_[start] << ":" << endl;
	for (const pair<int, int>& visit : order) {
		cout << names_[visit.first] << " (distance " << visit.second << ")" << endl;
	}
	cout << "Reachable: " << order.size() << " of " << names_.size()
	     << " buildings" << endl;
}

vector<int> CampusGraph::shortestPath(int start, int dest) const{
	vector<int> path;
	if (start==dest){
		path.push_back(start);
		return path;
	}


	vector<bool> visited(names_.size(), false);
	vector<int> parent(names_.size(), -1);
	queue<int> q;
	bool found = false;

	visited[start] = true;
	q.push(start);

	while (!q.empty() && !found) {
		int current = q.front();
		q.pop();
		for (int next : adjacency_[current]) {
			if (!visited[next]) {
				visited[next] = true;
				parent[next] = current;
				q.push(next);
				if (next == dest) { found = true; break; }
			}
		}
	}

	if (!found) return path;

	for (int v = dest; v != -1; v = parent[v]) path.push_back(v);
	reverse(path.begin(), path.end());
	return path;
}


void CampusGraph::displayShortestPath(const string& startName, const string& destName) const {
	string s = trimText(startName);
	string d = trimText(destName);
	if (s.empty() || d.empty()) {
		cout << "Error: building name cannot be blank." << endl;
		return;
	}

	int start = findBuilding(s);
	int dest = findBuilding(d);
	bool bad = false;
	if (start == -1) { cout << "Error: start building \"" << s << "\" was not found." << endl; bad = true; }
	if (dest == -1)  { cout << "Error: destination building \"" << d << "\" was not found." << endl; bad = true; }
	if (bad) return;

	vector<int> path = shortestPath(start, dest);
	if (path.empty()) {
		cout << "No path exists from " << names_[start] << " to " << names_[dest] << "." << endl;
		return;
	}

	cout << "\nShortest path:" << endl;
	for (int v : path) cout << names_[v] << endl;
	cout << "Number of connections: " << path.size() - 1 << endl;
}

int CampusGraph::countComponents() const {
	vector<bool> visited(names_.size(), false);
	int components = 0;

	for (int i = 0; i < static_cast<int>(names_.size()); i++) {
		if (visited[i]) continue;

		components++;
		queue<int> q;
		visited[i] = true;
		q.push(i);

		while (!q.empty()) {
			int current = q.front();
			q.pop();
			for (int next : adjacency_[current]) {
				if (!visited[next]) {
					visited[next] = true;
					q.push(next);
				}
			}
		}
	}
	return components;
}

void CampusGraph::displayConnectivityReport() const {
	cout << "\nGraph Connectivity Report" << endl;

	if (names_.empty()) {
		cout << "No buildings are loaded." << endl;
		cout << "Total buildings: 0" << endl;
		cout << "Total connections: 0" << endl;
		cout << "Connected components: 0" << endl;
		return;
	}
	cout << "Total buildings: " << names_.size() << endl;
	cout << "Total connections: " << connectionCount_ << endl;

	int maxDegree = 0;
	for (int i = 0; i < static_cast<int>(names_.size()); i++) {
		if (getDegree(i) > maxDegree) maxDegree = getDegree(i);
	}

	cout << "Highest degree (" << maxDegree << "): ";
	bool first = true;
	for (int i = 0; i < static_cast<int>(names_.size()); i++) {
		if (getDegree(i) == maxDegree) {
			if (!first) cout << ", ";
			cout << names_[i];
			first = false;
		}
	}
	cout << endl;

	cout << "Isolated buildings: ";
	first = true;
	for (int i = 0; i < static_cast<int>(names_.size()); i++) {
		if (getDegree(i) == 0) {
			if (!first) cout << ", ";
			cout << names_[i];
			first = false;
		}
	}
	if (first) cout << "None";
	cout << endl;

	cout << "Connected components: " << countComponents() << endl;
}

