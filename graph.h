#ifndef GRAPH__T
#define GRAPH__T

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "node.h"
class Graph{
public:
    Graph();
    ~Graph();

    void addNode(Node& n);
    void addName(const std::string& name);
    void DFS(std::string& result);
    void findTag(const std::string& tag, std::vector<Node>::iterator& ptr);
    void iterate(std::vector<Node>::iterator);
    void visit(std::vector<Node>::iterator& ptr);
    void unvisit(std::vector<Node>::iterator& ptr);
    bool there_is_unused_instr();
    bool has_loop();
private:
    std::vector<Node> v;
    std::string name;
    bool there_is_loop = false;
};
#endif
