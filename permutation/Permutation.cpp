#include <iostream>
#include "two_queues.hpp"
#include <filesystem>
#include <fstream>
#include <string>

int main(int argc, char* argv[]){
    std::cout<< "This program is to return the permulation of the input data."
            <<std::endl;
    
    int k = std::stoi(argv[1]);
    std::filesystem::path input_file_path(argv[2]);
    std::ifstream input_file;
    input_file.open(input_file_path);
    RandomizedQueue<std::string> RQ_ins{};
    while(!input_file.eof()){
        std::string temp;
        input_file>>temp;
        if(input_file.peek()==EOF){break;}
        RQ_ins.enqueue(temp);
    }
    
    auto RQ_iter= RQ_ins.iterator();
    int i=0;
    while(RQ_iter.has_next() && i<k ){
        std::cout<<*RQ_iter<<std::endl;
        ++i;
        ++RQ_iter;
    }

    


}
