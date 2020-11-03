#ifndef FINDDAG__T
#define FINDDAG__T
#include <sstream>
#include <iostream>
#include <fstream>

#include "fileHandler.h"
#include "graph.h"
#include "node.h"
#include "resultProtected.h"
#include <string>
#include "thread.h"
class FindDAG : public Thread{
public:
    FindDAG(FileHandler& fh, ResultProtected& r);
    virtual void run() override;
    void setGraphFromFile(std::string fileName, Graph& g);
    void operator()();
private:
    FileHandler& fileHandler;
    ResultProtected& results;
    bool thereIsFile = true;
};

#endif
