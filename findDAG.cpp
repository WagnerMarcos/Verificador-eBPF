#include "findDAG.h"
FindDAG::FindDAG(FileHandler& fh, ResultProtected& r):
    fileHandler(fh),
    results(r)
    {}

void FindDAG::run() {
    std::string fileName;
    std::string result;

    while(thereIsFile){
        result = "";
        fileName = fileHandler.getFile();
        if(fileName.length()>0){
            setGraphFromFile(fileName, result);
            results.ingresarResult(result);
        }
        else
            thereIsFile = false;
    }
// results.printResults();
}
void FindDAG::operator()(){
    this->run();
}
 
void FindDAG::setGraphFromFile(std::string fileName, std::string& result){
    std::string line;
    Graph g;
    g.addName(fileName);
    std::string word;
    std::ifstream f;
    // cout << endl << endl<< "Por trabajar: " << fileName << endl;
    std::string jmp_cmd[10]={"jmp","ja","jeq","jneq","jne","jlt","jle","jgt","jge","jset"};
    f.open(fileName);
    while(getline(f,line)){
        // Node node2;
        if(line.length() == 0)
            continue;
        Node node;
        std::istringstream sin(line);
        int j = 0;
        for(j=0, sin >> word; sin && word.length()>0; sin>>word){
            if(word[word.length()-1]==':'){
                node.set_tag(word);
                continue;
            }
            node.set_instr(word);
            for(int i = 0; i<10 ; i++){
                if(word == jmp_cmd[i]){
                    sin >> word;
                    while(sin && word.length()>0){
                        j++;
                        if(word[0]!='#'){
                            node.add_jmp_dest(word);
                        }
                        sin >> word;
                    }
                    break;
                }
            }
            if(word == "ret"){
                node.set_as_return();
            }
        }
        if(j==2 && node.has_jmp())
            node.set_as_conditional_jump();
        // std::cout << "PreGuarde" << std::endl;
        g.addNode(node);
        // std::cout << "Guarde" << std::endl;
        // node.reset();
    }
    // g.print();
    g.DFS(result);
}