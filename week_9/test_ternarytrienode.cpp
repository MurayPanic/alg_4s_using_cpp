#include <iostream>
#include <filesystem>

#include "gtest/gtest.h"

#define GTEST_COUT std::cout<<"[CUSTOM INFO] "
#define GTEST_LINE_HEADER "[          ] "

#define private public
        #include "TernaryTrieNode.hpp"
#undef private

TEST(TernaryTrieNode_constructor, case_1){
	TernaryTrieNode TTN_ins{};

}

TEST(TernaryTrieNode_constructor, case_2){
	TernaryTrieNode TTN_ins('a');

}

TEST(TernaryTrieNode_constructor, case_3){
	TernaryTrieNode TTN_ins('a',10);

}

int main(int argc, char* argv[]){
        std::cout<<"This script is to test the TernaryTrieNode.hpp head file."
                << std::endl;
        ::testing::InitGoogleTest( &argc, argv);
        return RUN_ALL_TESTS();

}

