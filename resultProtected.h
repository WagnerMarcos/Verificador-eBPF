#ifndef RESULTPROTECTED__T
#define RESULTPROTECTED__T

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "lock.h"
class ResultProtected{
private:
    std::vector<std::string> results;
    std::mutex m;
public:
    ResultProtected();
    ~ResultProtected();
    void ingresarResult(std::string result);
    void printResults();
};

#endif
