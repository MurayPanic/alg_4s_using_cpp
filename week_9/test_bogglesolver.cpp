#include <iostream>
#include <filesystem>

#include "gtest/gtest.h"

#define GTEST_COUT std::cout<<"[CUSTOM INFO] "
#define GTEST_LINE_HEADER "[          ] "

#define private public
	#include "BoggleSolver.hpp"
#undef private

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

TEST(BoggleSolver_constructor, case_1){

		BoggleSolver BS_ins{};
}


TEST(BoggleSolver_constructor, case_2){
		std::string file_name = "/boggle/dictionary-algs4.txt";
		auto dict_vec = read_dict(file_name);
		BoggleSolver BS_ins(dict_vec);
}

TEST(BoggleSolver_getAllValidWords, case_1){
		std::string file_name = "/boggle/dictionary-algs4.txt";
		auto dict_vec = read_dict(file_name);
		BoggleSolver BS_ins(dict_vec);
		std::string filename="/boggle/board4x4.txt";
                BoggleBoard BB_ins(filename);

		auto all_valid_words = BS_ins.getAllValidWords(BB_ins);

		GTEST_COUT<<"Now print all the valid words"<<std::endl;
		for(auto word : all_valid_words){
			std::cout<< GTEST_LINE_HEADER<<word<<std::endl;
		}

}

TEST(BoggleSolver_getAllValidWords, case_2){
		std::string file_name = "/boggle/dictionary-algs4.txt";
		auto dict_vec = read_dict(file_name);
		BoggleSolver BS_ins(dict_vec);
		std::string filename="/boggle/board-q.txt";
                BoggleBoard BB_ins(filename);

		auto all_valid_words = BS_ins.getAllValidWords(BB_ins);

		GTEST_COUT<<"Now print all the valid words"<<std::endl;
		for(auto word : all_valid_words){
			std::cout<< GTEST_LINE_HEADER<<word<<std::endl;
		}

}
TEST(BoggleSolver_dict,case_1){
		std::string file_name = "/boggle/dictionary-algs4.txt";
		auto dict_vec = read_dict(file_name);
		BoggleSolver BS_ins(dict_vec);
		EXPECT_TRUE(BS_ins.dictionary_set.contains("ON") );
}

TEST(BoggleSolver_scoreOf, case_1){
		std::string file_name = "/boggle/dictionary-algs4.txt";
		auto dict_vec = read_dict(file_name);
		BoggleSolver BS_ins(dict_vec);
		std::string filename="/boggle/board4x4.txt";
                BoggleBoard BB_ins(filename);

		auto all_valid_words = BS_ins.getAllValidWords(BB_ins);

		int score{0};
		for(auto word : all_valid_words){
			score += BS_ins.scoreOf(word);
		}

		GTEST_COUT<<"Now total score is "<<score<<std::endl;
}

TEST(BoggleSolver_scoreOf, case_2){
		std::string file_name = "/boggle/dictionary-algs4.txt";
		auto dict_vec = read_dict(file_name);
		BoggleSolver BS_ins(dict_vec);
		std::string filename="/boggle/board-q.txt";
                BoggleBoard BB_ins(filename);

		auto all_valid_words = BS_ins.getAllValidWords(BB_ins);

		int score{0};
		for(auto word : all_valid_words){
			score += BS_ins.scoreOf(word);
		}
		GTEST_COUT<<"Now total score is "<<score<<std::endl;


}

TEST(BoggleSolver_scoreOf, case_3){
		std::string file_name = "/boggle/dictionary-yawl.txt";
		auto dict_vec = read_dict(file_name);
		BoggleSolver BS_ins(dict_vec);

		std::string filename="/boggle/board-points26539.txt";
                BoggleBoard BB_ins(filename);

		auto all_valid_words = BS_ins.getAllValidWords(BB_ins);

		int score{0};
		for(auto word : all_valid_words){
			score += BS_ins.scoreOf(word);
		}
		GTEST_COUT<<"Now total score is "<<score<<std::endl;


}
int main(int argc, char* argv[]){
	std::cout<<"This script is to test the BoggleSolver.hpp head file."
		<< std::endl;
	::testing::InitGoogleTest( &argc, argv);
	return RUN_ALL_TESTS();

}
