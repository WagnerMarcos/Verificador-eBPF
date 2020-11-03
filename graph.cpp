#include "graph.h"

Graph::Graph(){}
Graph::~Graph(){}
void Graph::findTag(std::string tag){
    std::cout << "Aca" << std::endl;
    for (auto& node : v){
        if(node.getTag() == tag){
            std::cout << "Encontrado" << std::endl;
        }
    }
}


void Graph::addNode(Node& n){
    // std::cout << "Agrego nodo. Tamaño vector: " << v.size() << std::endl;
    // n.print();
    v.push_back(n);
    // std::cout << "Agregado. Tamaño vector: " << v.size() << std::endl << std::endl;
}

void Graph::print(){
    std::cout << std::endl << "Estoy por imprimir grafo:" << std::endl;
    for (auto node : v){
        node.print();
    }
}
void Graph::visit(std::vector<Node>::iterator& ptr){
    if(ptr->already_visited()){
        there_is_loop = true;
        // std::cout << "Cambiando a loop" << std::endl;
    }
}
void Graph::unvisit(std::vector<Node>::iterator& ptr){
    ptr->unvisit();
}
void Graph::findTag(std::string tag, std::vector<Node>::iterator& ptr){
    // std::cout << "Busco el tag:"<< tag << std::endl;
    ptr = v.begin();
    for(auto& node : v){
        if(tag == node.getTag()){
            // std::cout << "Encontre el tag" << std::endl;
            return;
        }
        else
            ptr++;
    }
    return;
}

void Graph::DFS(std::string& result){

    std::vector<Node>::iterator ptr = v.begin();
    iterate(ptr);
    result += name;
    if(has_loop())
        result += " FAIL: cycle detected";
        // std::cout << name << " FAIL: cycle detected" << std::endl;
    else if(there_is_unused_instr())
        result += " FAIL: unused instructions detected";
        // std::cout << name << " FAIL: unused instructions detected" << std::endl;
    else
        result += " GOOD";
        // std::cout << name << " GOOD" << std::endl;
    // saveResults(result);
}

bool Graph::there_is_unused_instr(){
    for(auto& node: v){
        if(!(node.was_used())){
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
    for(; ptr < v.end(); ptr++,i++){
        //  std::cout << std::endl << "Corriendo algoritmo, paso:   " << i << std::endl;
        visit(ptr);
        // ptr->print_instr();
        ptr->use();
        // std::cout << "has_jmp: " << ptr->has_jmp() << std::endl;
        // std::cout << "!(ptr->already_jumped(): " << !(ptr->already_jumped()) << std::endl;
        if(ptr->has_jmp() && !(ptr->already_jumped())){
            ptr->is_jumping();
            std::string tag = ptr->getFirstJump();
            // std::cout << "Tiene tag:" << tag << std::endl;
            std::vector<Node>::iterator ptr_to_tag;
            findTag(tag, ptr_to_tag);
            iterate(ptr_to_tag);

            std::string tag2 = ptr->getSecondJump();
            if(tag2.length() > 0){
                // std::cout << "Tiene tag2: " << tag2 << std::endl;
                std::vector<Node>::iterator ptr_to_tag2;
                findTag(tag2, ptr_to_tag2);
                iterate(ptr_to_tag2);
            }
            if(!(ptr->is_conditional_jump()))
                return;
        }
        if(ptr->is_return()){
            unvisit(ptr);
            return;
        }
        unvisit(ptr);
    }
}

void Graph::addName(std::string str){
    // std::cout << "str: " << str << std::endl;
    name = str;
    // std::cout << "name: " << name << std::endl;
}