#ifndef FILEHANDLER__T
#define FILEHANDLER__T

#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <mutex>
#include "lock.h"

class FileHandler {
private:
    std::mutex m;
    std::queue <std::string> q;
public:
    FileHandler();
    ~FileHandler();
    void handleFile(const char *fileName);
    bool hasFile();
    std::string getFile();
};

#endif
