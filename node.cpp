#include "node.h"
Node::Node(){
    is_jmp = false; 
    is_used = false;
    is_ret = false;
    visited = false; 
    has_conditional_jump = false;
    jumped = false;
}
Node::~Node(){}
Node::Node(const Node& node){
    is_jmp = false; 
    is_used = false;
    is_ret = false;
    visited = false; 
    jumped = false;
    has_conditional_jump = false;
    
    if (node.instr.length()>0)
        this->instr = node.instr;
    if (node.tag.length()>0)
        this->tag = node.tag;
    if (node.first_dest.length()>0)
        this->first_dest = node.first_dest;
    if (node.second_dest.length()>0)
        this->second_dest = node.second_dest;
    this->is_jmp = node.is_jmp;
    this->is_used = node.is_used;
    this->is_ret = node.is_ret;
    this->visited = node.visited;
    this->jumped = node.jumped;
    this->has_conditional_jump = node.has_conditional_jump;
}
void Node::reset(){
    is_jmp = false; 
    is_used = false;
    is_ret = false;
    visited = false; 
    has_conditional_jump = false;
    jumped = false;
    tag = "";
    instr = "";
    first_dest = "";
    second_dest = "";
}
void Node::set_instr(std::string str){
    if (str.length() > 0)
        instr = str;
}
void Node::print_instr(){
    std::cout << "Instruccion: " << instr << std::endl;
}
std::string Node::getTag(){
    return tag;
}
void Node::set_tag(std::string new_tag){
    this->tag = new_tag;
    if (!this->tag.empty())
        this->tag.pop_back();
}
void Node::add_jmp_dest(std::string new_dest){
    if (is_jmp == false)
        is_jmp = true;
    if (first_dest.length() == 0){
        first_dest = new_dest;
    } else {
        second_dest = new_dest;
        first_dest.pop_back();
    }
}
void Node::print(){
    std::cout << "Imprimiendo todo el nodo: " << std::endl;

    std::list<std::string>::iterator it;
    std::cout << "tag:" << tag << "~" << std::endl;
    std::cout << "is return: " << is_ret << std::endl;
    std::cout << "is jmp: " << is_jmp << std::endl;
    std::cout << "first_dest: " << first_dest << std::endl;
    std::cout << "second_dest: " << second_dest << std::endl;
    std::cout << "has_conditional_jump: " << has_conditional_jump << std::endl;
}
void Node::use(){
    is_used = true;
}
bool Node::was_used(){
    return is_used;
}
bool Node::is_return(){
    return is_ret;
}
bool Node::has_jmp(){
    return is_jmp;
}
void Node::set_as_return(){
    is_ret = true;
}
bool Node::already_visited(){
    if (visited == false){
        visited = true;
        return false;
    } else 
        return true;
}
void Node::unvisit(){
    visited = false;
}
std::string Node::getFirstJump(){
    return first_dest;
}

std::string Node::getSecondJump(){
    return second_dest;
}

void Node::set_as_conditional_jump(){
    has_conditional_jump = true;
}

bool Node::is_conditional_jump(){
    return has_conditional_jump;
}
bool Node::already_jumped(){
    return jumped;
}
void Node::is_jumping(){
    jumped = true;
}
