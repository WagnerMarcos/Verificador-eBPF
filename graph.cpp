#include "graph.h"

Graph::Graph(){}
Graph::~Graph(){}

void Graph::addNode(Node& n){
    v.push_back(n);
}

void Graph::visit(std::vector<Node>::iterator& ptr){
    if (ptr->already_visited()){
        there_is_loop = true;
    }
}
void Graph::unvisit(std::vector<Node>::iterator& ptr){
    ptr->unvisit();
}
void Graph::findTag(const std::string& tag, std::vector<Node>::iterator& ptr){
    ptr = v.begin();
    for (auto& node : v){
        if (tag == node.getTag()){
            return;
        } else {
            ptr++;
        }
    }
    return;
}

void Graph::DFS(std::string& result){
    std::vector<Node>::iterator ptr = v.begin();
    iterate(ptr);
    result += name;
    if (has_loop())
        result += " FAIL: cycle detected";
    else if (there_is_unused_instr())
        result += " FAIL: unused instructions detected";
    else
        result += " GOOD";
}

bool Graph::there_is_unused_instr(){
    for (auto& node: v){
        if (!(node.was_used())){
            return true;
        }
    }
    return false;
}
bool Graph::has_loop(){
    return there_is_loop;
}
void Graph::iterate(std::vector<Node>::iterator ptr){
    int i = 0;
    for (; ptr < v.end(); ++ptr,i++){
        visit(ptr);
        ptr->use();
        if (ptr->has_jmp() && !(ptr->already_jumped())){
            ptr->is_jumping();
            std::string tag = ptr->getFirstJump();
            std::vector<Node>::iterator ptr_to_tag;
            findTag(tag, ptr_to_tag);
            iterate(ptr_to_tag);
            std::string tag2 = ptr->getSecondJump();
            if (tag2.length() > 0){
                std::vector<Node>::iterator ptr_to_tag2;
                findTag(tag2, ptr_to_tag2);
                iterate(ptr_to_tag2);
            }
            if (!(ptr->is_conditional_jump()))
                return;
        }
        if (ptr->is_return()){
            unvisit(ptr);
            return;
        }
        unvisit(ptr);
    }
}

void Graph::addName(const std::string& str){
    name = str;
}
