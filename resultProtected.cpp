#include "resultProtected.h"

ResultProtected::ResultProtected(){}
ResultProtected::~ResultProtected(){}

void ResultProtected::ingresarResult(std::string result){
    Lock l(m);
    results.push_back(result);
}
void ResultProtected::printResults(){
    std::sort(results.begin(),results.end());//,sorting);
    for(auto& str : results)
        std::cout << str << std::endl;        
}
