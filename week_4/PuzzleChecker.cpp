#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include "Solver.hpp"

std::vector<int> create_board_vec(std::filesystem::path test_file_path){
	std::ifstream input_file;
	input_file.open(test_file_path);
	int board_size{0};
	std::string board_size_str;
	input_file>>board_size_str;
	board_size = std::stoi(board_size_str);
	std::vector<int> board_vec;
	while(!input_file.eof()){
		std::string tmp_num_str;
		input_file>>tmp_num_str;
		if(input_file.peek()==EOF){break;}
		int tmp_num = std::stoi(tmp_num_str);
		board_vec.push_back(tmp_num);
		
	}
	return board_vec;
}

int main(int argc, char* argv[]){
	std::cout<<"This program is to conduct test on the A* algorithm for 8puzzle"<<std::endl;

	std::filesystem::path test_folder_path(argv[1]);
	for(auto&p : std::filesystem::directory_iterator( test_folder_path) ){
		std::string file_name = p.path();
		if(file_name.ends_with("txt")){
			std::cout<< "Now process: "<<file_name<<std::endl;
			std::vector<int> board_vec= create_board_vec(file_name);			
			/*Debug ouput
			for(auto item : board_vec){
				std::cout<<item<<",";
			}
			std::cout<<std::endl;
			*/

			Board board_ins(board_vec);
			/*
			if(board_ins.dimension()>3){
				std::cout<<"Skip board larger than 3x3"<<std::endl;
				continue;}
			*/
			std::cout<< "The board is:" << std::endl;
			std::cout<< board_ins.toString() << std::endl;
			Solver solver_ins(board_ins);
			if(solver_ins.isSolvable()){
				std::cout<<"Minimum number of moves = "
					<<solver_ins.moves()
					<<std::endl;
			}else{
				std::cout<<"No solution possible"
					<<std::endl;
			}
			std::cout<<"-------------------------------------"
				<<std::endl;

		}
	}

}
