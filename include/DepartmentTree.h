#ifndef DEPARTMENTTREE_H
#define DEPARTMENTTREE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class DepartmentTree {
private:
    struct Node {
        string name;
        Node* parent;
        vector<Node*> children;

        Node(string departmentName, Node* parentNode = nullptr);
    };

    Node* root;

    Node* findNode(const string& name) const;
    void deleteTree(Node* node);

    void displayPreorder(Node* node, int depth) const;
    void preorder(Node* node) const;
    void postorder(Node* node) const;

    int countDepartments(Node* node) const;
    int countLeaves(Node* node) const;
    int calculateHeight(Node* node, int depth) const;

    string toLowerCase(const string& text) const;
    string trim(const string& text) const;

public:
    DepartmentTree();
    ~DepartmentTree();

    bool loadFromFile(const string& filename);

    bool addDepartment(const string& name,
                       const string& parentName = "");

    void searchDepartment(const string& name) const;

    void displayHierarchy() const;

    void displayPreorder() const;
    void displayPostorder() const;
    void displayLevelOrder() const;

    void displayStatistics() const;

    bool isEmpty() const;
};

#endif
