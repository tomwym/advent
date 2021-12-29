#pragma once

namespace advent21 {

class Node12 {
public:
    Node12();
    Node12(const std::string&);
    void insert(Node12* const);
    std::vector<Node12*> nexts;
    std::string name;
    bool size; // true is large, false is small
};

Node12::Node12() : nexts({nullptr}), name(""), size(false) { }

Node12::Node12(const std::string& _name) : nexts({nullptr}), name(_name), size(false) {
    size = (bool)std::isupper(_name[0]);
    // std::cout << "inserting " << _name << " with size " << size << '\n';
}

void Node12::insert(Node12* const _next) {
    nexts.push_back(_next);
}

class Node12_Container {
public:
    Node12_Container();
    ~Node12_Container();
    void insert(const std::string&);
    Node12* find(const std::string&);
    std::vector<Node12*> container;
};

Node12_Container::Node12_Container() : container({}) {}

// cleanup! first implementation of RAII ever 
Node12_Container::~Node12_Container() {
    for (auto np : container) {
        delete np;
    }
    container.clear();
}

void Node12_Container::insert(const std::string& _name) {
    Node12* temp = new Node12(_name);
    container.push_back(temp);
}

Node12* Node12_Container::find(const std::string& _name) {
    for (const auto& np : container) {
        if (np->name == _name) {
            return np;
        }
    }
    return nullptr;
}

// purely for finding the node in graph with corresponding name
Node12* preTraversal(Node12* const root, const std::string& search, std::set<Node12*>& visited) {
    if (root == nullptr) {
        return nullptr;
    }
    // if already seen 
    if (visited.find(root) != visited.end()) {
        return nullptr;
    } else {
        visited.insert(root);
    }
    
    if (root->name == search) {
        return root;
    }

    for (const auto& n : root->nexts) {
        if (n != nullptr) {
            Node12* out = preTraversal(n, search, visited);
            if (out != nullptr) {
                return out;
            }
        }
    }
    return nullptr;
}

void printPath(std::stack<std::string> path, const std::map<Node12*, int>& visited) {
    std::vector<std::string> temp {};
    while (!path.empty()) {
        temp.push_back(path.top());
        path.pop();
    }

    for (auto it=temp.rbegin(); it!=temp.rend(); it++) {
        std::cout << *it << ',';
    }
    std::cout << "end" << '\n';
}

int nmaxval(const std::map<Node12*, int>& visited, const int limit) {
    int n = 0;
    for (const auto& p : visited) {
        if (p.first != nullptr) {
            if (p.second >= limit) {
                n++;
            }
        }
    }
    return n;
}

int DEPTHFIRSTSEARCH_COUNT = 0;
void depthFirstSearch(Node12* const root, std::map<Node12*, int>& visited, 
                      std::stack<std::string>& path, Node12* const ROOT, const int key) {
    // conditions for backtracking // 
    // if root is null
    if (root == nullptr) {
        return;
    }
    // only visit the 'start' node once
    if (root == ROOT && visited[root] > 0) {
        return;
    }
    // if there is more than one node with more than one visit, return early
    if (nmaxval(visited, 2)>1) {
        return;
    }
    // if lower case, and has the key has been visited
    // and if the number of times it is visited is already that specified by key
    // then return early    
    if (!root->size && visited.count(root) && visited[root]>=key) {
        return;
    // if lower case, and has the key has been visited
    } else if (!root->size && visited.count(root)) {
        visited[root]++;
    // 
    } else if (!root->size) {
        visited[root] = 1;
    }

    // if at the end of the maze
    if (root->name == "end") {
        // printPath(path, visited);
        // every time we backtrack we want to undo any insertions to visited
        visited[root]--;
        DEPTHFIRSTSEARCH_COUNT++;
        return;
    }

    path.push(root->name);
    // otherwise keep searching
    for (const auto& n : root->nexts) {
        if (n != nullptr) {
            depthFirstSearch(n, visited, path, ROOT, key);
        }
    }
    // why release before popping? wtf
    // same thing, backtrack while releasing top from visited set
    visited[root]--;
    path.pop();
    return;
}

template<typename T>
class Sol12 : public Base {
public:
    Sol12(const std::string&);
    void Solution1();
    void Solution2();
    T Day12();
private:
    std::vector<std::vector<T>> obj;
    // create the graph from the input and store in a container (RAII)
    Node12_Container node_container;
};

template<typename T>
Sol12<T>::Sol12(const std::string& nums)
: Base(nums), node_container({}) {

    obj = ReadVVT<T>(this->filename, '-');
    std::set<std::string> node_name_collection{};

    // first create nodes for all objects
    for (const auto& r : obj) {
        std::string s_parent({r[0]});
        std::string s_child({r[1]});
        // if parent doesnt exists
        if (node_name_collection.find(s_parent) == node_name_collection.end()) {
            node_container.insert(s_parent);
            node_name_collection.insert(s_parent);
        } 
        // if child doesnt exists
        if (node_name_collection.find(s_child) == node_name_collection.end()) {
            node_container.insert(s_child);
            node_name_collection.insert(s_child);
        }
    }
    
    // link nodes together as a graph
    for (const auto& r : obj) {
        std::string s_parent({r[0]});
        std::string s_child({r[1]});

        Node12* n_parent = node_container.find(s_parent);
        Node12* n_child = node_container.find(s_child);
        n_parent->insert(n_child);
        n_child->insert(n_parent);
    }
}

template<typename T>
T Sol12<T>::Day12() {
    return { };
}


template<typename T>
void Sol12<T>::Solution1() {

    Node12* const ROOT = node_container.find("start");

    std::map<Node12*, int> visited {};
    std::stack<std::string> path {};
    DEPTHFIRSTSEARCH_COUNT = 0;
    depthFirstSearch(ROOT, visited, path, ROOT, 1);

    std::cout << DEPTHFIRSTSEARCH_COUNT << " solution1" << std::endl;
}

template<typename T>
void Sol12<T>::Solution2() {

    Node12* const ROOT = node_container.find("start");

    std::map<Node12*, int> visited {};
    std::stack<std::string> path {};
    DEPTHFIRSTSEARCH_COUNT = 0;
    depthFirstSearch(ROOT, visited, path, ROOT, 2);

    std::cout << DEPTHFIRSTSEARCH_COUNT << " solution2" << std::endl;
    
}
}