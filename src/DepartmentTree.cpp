#include "DepartmentTree.h"

#include <fstream>
#include <algorithm>
#include <cctype>
#include <queue>

// Constructor for a department node
DepartmentTree::Node::Node(string departmentName, Node* parentNode) {
    name = departmentName;
    parent = parentNode;
}

// Constructor for the tree
DepartmentTree::DepartmentTree() {
    root = nullptr;
}

// Destructor
DepartmentTree::~DepartmentTree() {
    deleteTree(root);
}

// Delete all nodes in the tree
void DepartmentTree::deleteTree(Node* node) {
    if (node == nullptr) {
        return;
    }

    for (Node* child : node->children) {
        deleteTree(child);
    }

    delete node;
}

// Check whether the tree is empty
bool DepartmentTree::isEmpty() const {
    return root == nullptr;
}

// Convert text to lowercase for comparisons
string DepartmentTree::toLowerCase(const string& text) const {
    string result = text;

    transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) {
            return static_cast<char>(tolower(c));
        });

    return result;
}

// Remove spaces at the beginning and end
string DepartmentTree::trim(const string& text) const {
    size_t start = text.find_first_not_of(" \t\r\n");

    if (start == string::npos) {
        return "";
    }

    size_t end = text.find_last_not_of(" \t\r\n");

    return text.substr(start, end - start + 1);
}

// Find a department by name
DepartmentTree::Node* DepartmentTree::findNode(
    const string& name) const {

    if (root == nullptr) {
        return nullptr;
    }

    queue<Node*> nodes;
    nodes.push(root);

    while (!nodes.empty()) {
        Node* current = nodes.front();
        nodes.pop();

        if (toLowerCase(current->name) == toLowerCase(name)) {
            return current;
        }

        for (Node* child : current->children) {
            nodes.push(child);
        }
    }

    return nullptr;
}

// Add a department
bool DepartmentTree::addDepartment(
    const string& name, const string& parentName) {

    string departmentName = trim(name);
    string parent = trim(parentName);

    if (departmentName.empty()) {
        cout << "Department name cannot be empty.\n";
        return false;
    }

    // Check for duplicate department names
    if (findNode(departmentName) != nullptr) {
        cout << "Department already exists.\n";
        return false;
    }

    // If the tree is empty, create the root
    if (root == nullptr) {
        root = new Node(departmentName);
        cout << "Root department added successfully.\n";
        return true;
    }

    // Find the parent department
    Node* parentNode = findNode(parent);

    if (parentNode == nullptr) {
        cout << "Parent department not found.\n";
        return false;
    }

    // Create and attach the new department
    Node* newNode = new Node(departmentName, parentNode);

    parentNode->children.push_back(newNode);

    cout << "Department added successfully.\n";
    return true;
}

// Load departments from a file
bool DepartmentTree::loadFromFile(const string& filename) {
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open " << filename << ".\n";
        return false;
    }

    string line;
    int lineNumber = 0;

    while (getline(inputFile, line)) {
        lineNumber++;

        // Skip blank lines
        if (trim(line).empty()) {
            continue;
        }

        // Skip comment lines
        if (trim(line)[0] == '#') {
            continue;
        }

        size_t separator = line.find('|');

        if (separator == string::npos ||
            line.find('|', separator + 1) != string::npos) {
            cerr << filename << ":" << lineNumber
                 << ": Invalid record format.\n";
            continue;
        }

        string departmentName = trim(line.substr(0, separator));
        string parentName = trim(line.substr(separator + 1));

        if (departmentName.empty() || parentName.empty()) {
            cerr << filename << ":" << lineNumber
                 << ": Department or parent name is empty.\n";
            continue;
        }

        // The first accepted department must be the root
        if (root == nullptr) {
            if (toLowerCase(parentName) != "none") {
                cerr << filename << ":" << lineNumber
                     << ": First department must have NONE as parent.\n";
                continue;
            }

            addDepartment(departmentName);
        }
        else {
            if (toLowerCase(parentName) == "none") {
                cerr << filename << ":" << lineNumber
                     << ": Only the root can have NONE as parent.\n";
                continue;
            }

            if (!addDepartment(departmentName, parentName)) {
                cerr << filename << ":" << lineNumber
                     << ": Department was not loaded.\n";
            }
        }
    }

    inputFile.close();
    return true;
}

// Search for a department and display its information
void DepartmentTree::searchDepartment(const string& name) const {
    Node* found = findNode(trim(name));

    if (found == nullptr) {
        cout << "Department not found.\n";
        return;
    }

    int depth = 0;
    Node* current = found;

    while (current->parent != nullptr) {
        depth++;
        current = current->parent;
    }

    cout << "\nDepartment: " << found->name << endl;

    if (found->parent == nullptr) {
        cout << "Parent: None\n";
    }
    else {
        cout << "Parent: " << found->parent->name << endl;
    }

    cout << "Direct children: "
         << found->children.size() << endl;

    cout << "Depth: " << depth << endl;
}

// Display the hierarchy with indentation
void DepartmentTree::displayPreorder(Node* node, int depth) const {
    if (node == nullptr) {
        return;
    }

    for (int i = 0; i < depth; i++) {
        cout << "    ";
    }

    cout << node->name << endl;

    for (Node* child : node->children) {
        displayPreorder(child, depth + 1);
    }
}

void DepartmentTree::displayHierarchy() const {
    if (root == nullptr) {
        cout << "Department tree is empty.\n";
        return;
    }

    cout << "\nDepartment Hierarchy:\n";
    displayPreorder(root, 0);
}

// Preorder traversal
void DepartmentTree::preorder(Node* node) const {
    if (node == nullptr) {
        return;
    }

    cout << node->name << endl;

    for (Node* child : node->children) {
        preorder(child);
    }
}

void DepartmentTree::displayPreorder() const {
    if (root == nullptr) {
        cout << "Department tree is empty.\n";
        return;
    }

    cout << "\nPreorder Traversal:\n";
    preorder(root);
}

// Postorder traversal
void DepartmentTree::postorder(Node* node) const {
    if (node == nullptr) {
        return;
    }

    for (Node* child : node->children) {
        postorder(child);
    }

    cout << node->name << endl;
}

void DepartmentTree::displayPostorder() const {
    if (root == nullptr) {
        cout << "Department tree is empty.\n";
        return;
    }

    cout << "\nPostorder Traversal:\n";
    postorder(root);
}

// Level-order traversal using a queue
void DepartmentTree::displayLevelOrder() const {
    if (root == nullptr) {
        cout << "Department tree is empty.\n";
        return;
    }

    cout << "\nLevel-order Traversal:\n";

    queue<Node*> nodes;
    nodes.push(root);

    while (!nodes.empty()) {
        Node* current = nodes.front();
        nodes.pop();

        cout << current->name << endl;

        for (Node* child : current->children) {
            nodes.push(child);
        }
    }
}

// Count all departments
int DepartmentTree::countDepartments(Node* node) const {
    if (node == nullptr) {
        return 0;
    }

    int count = 1;

    for (Node* child : node->children) {
        count += countDepartments(child);
    }

    return count;
}

// Count departments with no children
int DepartmentTree::countLeaves(Node* node) const {
    if (node == nullptr) {
        return 0;
    }

    if (node->children.empty()) {
        return 1;
    }

    int count = 0;

    for (Node* child : node->children) {
        count += countLeaves(child);
    }

    return count;
}

// Calculate tree height
int DepartmentTree::calculateHeight(Node* node, int depth) const {
    if (node == nullptr) {
        return -1;
    }

    int maximumDepth = depth;

    for (Node* child : node->children) {
        maximumDepth = max(
            maximumDepth,
            calculateHeight(child, depth + 1)
        );
    }

    return maximumDepth;
}

// Display department statistics
void DepartmentTree::displayStatistics() const {
    cout << "\nDepartment Statistics:\n";

    if (root == nullptr) {
        cout << "Total departments: 0\n";
        cout << "Leaf departments: 0\n";
        cout << "Tree height: N/A\n";
        return;
    }

    cout << "Total departments: "
         << countDepartments(root) << endl;

    cout << "Leaf departments: "
         << countLeaves(root) << endl;

    cout << "Tree height: "
         << calculateHeight(root, 0) << endl;
}
