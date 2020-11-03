#include "resultProtected.h"
#include "fileHandler.h"
#include "findDAG.h"
#include "thread.h"
#include <string>
int main(int argc, char *argv[]){
    FileHandler fh; 
    int i = 2;
    std::string hello(argv[1]); 
    std::stringstream str(hello); 
    int n_threads;  
    str >> n_threads;  
    // int i = 2; //si hay hilos
    ResultProtected results;
    while(i < argc){
        fh.handleFile(argv[i]);
        i++;
    }
    std::vector<Thread*> threads;

    for(i = 0; i < n_threads; ++i){
        Thread *t = new FindDAG(fh, results);
        t->start();

        threads.push_back(t);
    }

    for(i = 0; i < n_threads; ++i){
        threads[i]->join();
        delete threads[i];
    }
    results.printResults();
    // FindDAG find_DAG = FindDAG(fh, results);
    // find_DAG();
    
    return 0;
}