#include <iostream>
#include <string>
#include <filesystem>
#include "BoggleSolver.hpp"

std::vector<std::string> read_dict(std::string file_name){

                std::string  file_path = std::filesystem::current_path();
                file_path.append(file_name);
                std::ifstream input_file;
                input_file.open(file_path);
                std::vector<std::string> result_dict;
                while(!input_file.eof()){
                        std::string word;
                        input_file >>word;
                        if(input_file.peek()==EOF){
                                break;
                        }
                        result_dict.push_back(word);
                }
                return result_dict;
}

int main(int argc, char* argv[]){
	
	std::string dict_file_name =argv[1];
	std::string board_file_name = argv[2];

	auto dictionary = read_dict(dict_file_name);
	BoggleBoard BB_ins(board_file_name);
	
	BoggleSolver BS_ins(dictionary);
	auto all_valid_words = BS_ins.getAllValidWords(BB_ins);
	int score{0};
	for(auto word : all_valid_words){
		std::cout<<word<<std::endl;
		score += BS_ins.scoreOf(word);
	}
	std::cout<<"Score = "<<score <<std::endl;


}
