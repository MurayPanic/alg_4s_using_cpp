#include <iostream>
#include <vector>
#include <string>


#include "Outcast.hpp"


std::vector<std::string> read_outcast_file(std::string outcast_file_dir){
    std::string cur_path = std::filesystem::current_path();
    std::string outcast_path_str =cur_path+"/"+outcast_file_dir;
    std::filesystem::path outcast_file_path(outcast_path_str);
    std::ifstream outcast_file;
    outcast_file.open(outcast_file_path);

    if(outcast_file.fail()){
        throw std::invalid_argument("The provided outcast file path is incorrect");
    }

    std::vector<std::string> nouns{};
    while(!outcast_file.eof()){
        std::string tmp;
        outcast_file >>tmp;
        if(outcast_file.peek()==EOF){break;}
        nouns.push_back(tmp);
    }
    return nouns;

}

int main(int argc, char* argv[]){
    std::cout<<"This is a test client of the outclast"<< std::endl;
    if(argc<2){
         throw std::invalid_argument("The provided parameter is not correct.");
    }

    std::string synset_path_str = argv[1];
    std::string hypernyms_path_str = argv[2];
    std::vector<std::string>  outcast_path_vec{};
    for(int i=3; i<argc; ++i){
        outcast_path_vec.push_back(argv[i]);

    }

    std::cout<<"Now build the wordnet..."<<std::endl;
    WordNet WN_ins(synset_path_str, hypernyms_path_str);
    Outcast OC_ins(WN_ins);

    std::cout<<"Now find the outcast..."<<std::endl;
    for(auto outcast_path_str : outcast_path_vec){
        std::cout<<outcast_path_str<<": ";
        std::vector<std::string> nouns = read_outcast_file(outcast_path_str);
        std::string outcast_noun = OC_ins.outcast(nouns);
        std::cout<< outcast_noun <<std::endl;

    }


    return 0;
}