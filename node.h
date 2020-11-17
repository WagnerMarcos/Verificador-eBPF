#ifndef NODE__T
#define NODE__T

#include <list>
#include <string>
#include <iostream>
class Node{
public:
    Node();
    ~Node();
    Node(const Node& node);
    std::string getTag();
    void set_tag(const std::string& tag);
    void set_instr(std::string str);
    void add_jmp_dest(const std::string& dest);
    void printTag();
    void set_as_return();
    bool is_return();
    bool has_jmp();
    bool already_visited();
    std::string getFirstJump();
    std::string getSecondJump();
    void set_as_conditional_jump();
    bool is_conditional_jump();
    bool already_jumped();
    void is_jumping();
    void unvisit();
    void use();
    bool was_used();

private:
    std::string tag;
    std::string instr;
    std::string first_dest;
    std::string second_dest;
    bool is_jmp;
    bool is_used;
    bool is_ret;
    bool visited;
    bool has_conditional_jump;
    bool jumped;
};
#endif
