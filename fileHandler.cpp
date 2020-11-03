#include "fileHandler.h"

FileHandler::FileHandler(){}
FileHandler::~FileHandler(){}

void FileHandler::handleFile(const char *fileName){
    q.push(std::string(fileName));
}

bool FileHandler::hasFile(){
    return !q.empty();
}

std::string FileHandler::getFile(){
    Lock l(m);
    if (hasFile()){
        std::string f = q.front(); // referencia al próximo elemento
        q.pop(); // quito el siguiente elemento de la queue
        return f;
    }
    return "";
}
