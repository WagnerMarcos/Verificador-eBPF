#include "resultProtected.h"
#include "fileHandler.h"
#include "findDAG.h"
#include "thread.h"
#include <string>
int main(int argc, char *argv[]){
    FileHandler fh; 
    int i = 2;
    std::string n_threads_arg(argv[1]); 
    std::stringstream aux_stream(n_threads_arg); 
    int n_threads;  
    aux_stream >> n_threads;  
    ResultProtected results;

    while (i < argc){
        fh.handleFile(argv[i]);
        i++;
    }
    std::vector<Thread*> threads;
    std::cout << " Aca " << std::endl;

    for (i = 0; i < n_threads; ++i){
        Thread *t = new FindDAG(fh, results);
        t->start();

        threads.push_back(t);
    }
    std::cout << " Aca2 " << std::endl;
    for (i = 0; i < n_threads; ++i){
        threads[i]->join();
    std::cout << " Aca3 " << std::endl;
        delete threads[i];
    }
    results.printResults();
    
    return 0;
}
