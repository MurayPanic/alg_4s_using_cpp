#include <iostream>
#include <filesystem>
#include <fstream>
#include "gtest/gtest.h"

#define private public
        #include "PrefixTree.hpp"
#undef private

#define GTEST_COUT std::cout<<"[CUSTOM INFO] "
#define GTEST_LINE_HEADER "[          ] "

std::vector<std::string> read_dict(std::string file_name){

                std::string  file_path = std::filesystem::current_path();
                file_path.append(file_name);
                std::ifstream input_file;
                input_file.open(file_path);
                std::vector<std::string> result_dict;
                while(!input_file.eof()){
                        std::string word;
                        input_file >>word;
			//std::cout<<word<<" is read"<<std::endl;
                       if(input_file.peek()==EOF){
                                break;
                        }
                        result_dict.push_back(word);
                }
                return result_dict;
}


TEST(PrefixTree_constructor, case_1){
	PrefixTree PT_ins{};
}

TEST(PrefixTree_constructor, case_2){
	std::vector<std::string> test_dict{"I", "AM", "A","DICT"};
	PrefixTree PT_ins(test_dict);

}

TEST(PrefixTree_constructor, case_3){
                std::string file_name = "/boggle/dictionary-algs4.txt";
                auto dict_vec = read_dict(file_name);

                PrefixTree PT_ins(dict_vec);
}

TEST(PrefixTree_has_word_with_prefix, case_1){
	std::vector<std::string> test_dict{"I", "AM", "A","DICT","FUCK"};
	PrefixTree PT_ins(test_dict);

	EXPECT_TRUE(PT_ins.has_word_with_prefix("AM"));
	EXPECT_TRUE(PT_ins.has_word_with_prefix("DI"));
	EXPECT_TRUE(PT_ins.has_word_with_prefix("I"));

	EXPECT_FALSE(PT_ins.has_word_with_prefix("SB"));
	EXPECT_FALSE(PT_ins.has_word_with_prefix("AMG"));
	EXPECT_FALSE(PT_ins.has_word_with_prefix("DICK"));

	

}


int main(int argc, char* argv[]){
        std::cout<<"This script is to test the PrefixTree.hpp head file."
                << std::endl;

        ::testing::InitGoogleTest(&argc,argv);
        return RUN_ALL_TESTS();

}


