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
    std::cout << "inserting " << _name << " with size " << size << '\n';
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

// purely for finding the node with corresponding name
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

void printPath(std::stack<std::string> path) {\
    std::vector<std::string> temp {};
    while (!path.empty()) {
        temp.push_back(path.top());
        path.pop();
    }
    for (auto it=temp.rbegin(); it!=temp.rend(); it++) {
        std::cout << *it << ',';
    }
    std::cout << '\n';
}

int DEPTHFIRSTSEARCH_COUNT = 0;
void depthFirstSearch(Node12* const root, std::set<Node12*>& visited, 
                      std::stack<std::string>& path, Node12* const ROOT) {
    // conditions for backtracking // 
    // if root is null
    if (root == nullptr) {
        return;
    }
    path.push(root->name);

    // if at the end of the maze
    if (root->name == "end") {
        printPath(path);
        // every time we backtrack we want to undo any insertions to visited
        std::set<Node12*> t_visited {};
        visited.erase(preTraversal(ROOT, path.top(), t_visited));
        path.pop();
        DEPTHFIRSTSEARCH_COUNT++;
        return;
    }

    // if lower case and has been visited
    if (!root->size && visited.find(root) != visited.end()) {
        path.pop();
        return;
    } else if (!root->size) {
        visited.insert(root);
    }

    // otherwise keep searching
    for (const auto& n : root->nexts) {
        if (n != nullptr) {
            depthFirstSearch(n, visited, path, ROOT);
        }
    }
    // why release before popping? wtf
    // same thing, backtrack while releasing top from visited set
    std::set<Node12*> t_visited {};
    visited.erase(preTraversal(ROOT, path.top(), t_visited));
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
};

template<typename T>
Sol12<T>::Sol12(const std::string& nums)
: Base(nums) { }

template<typename T>
T Sol12<T>::Day12() {
    return { };
}


template<typename T>
void Sol12<T>::Solution1() {
    obj = ReadVVT<T>(this->filename, '-');
    std::set<std::string> node_name_collection{};

    // create the graph from the input and store in a container (RAII)
    Node12_Container node_container;
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

    // link nodes together as a directed acyclic graph
    Node12* const ROOT = node_container.find("start");
    for (const auto& r : obj) {
        std::string s_parent({r[0]});
        std::string s_child({r[1]});

        Node12* n_parent = node_container.find(s_parent);
        Node12* n_child = node_container.find(s_child);
        n_parent->insert(n_child);
        n_child->insert(n_parent);
    }

    // test preorder traversal algo here
    for (const auto& r : obj) {
        std::string s_parent({r[0]});
        std::string s_child({r[1]});
        Node12* n_parent;
        Node12* n_child;
        std::set<Node12*> p_visited {};
        n_parent = preTraversal(ROOT, s_parent, p_visited);
        std::set<Node12*> c_visited {};
        n_child = preTraversal(ROOT, s_child, c_visited);

        // std::cout << n_parent << ' ' << n_parent->name << '\n';
        // std::cout << n_child << ' ' << n_child->name << '\n' << '\n';
    }
    std::set<Node12*> visited {};
    std::stack<std::string> path {};
    DEPTHFIRSTSEARCH_COUNT = 0;
    depthFirstSearch(ROOT, visited, path, ROOT);

    std::cout << DEPTHFIRSTSEARCH_COUNT << " solution1" << std::endl;
}

template<typename T>
void Sol12<T>::Solution2() {
    std::cout << " solution2" << std::endl;
}

}
