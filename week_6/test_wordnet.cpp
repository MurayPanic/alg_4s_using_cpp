#include <iostream>
#include <gtest/gtest.h>
#include "WordNet.hpp"

#define GTEST_COUT std::cout<< "[CUSTOM INFO] "

TEST(WordNet_constructor, case_1){
	WordNet WN_ins{};
}


TEST(WordNet_constructor, case_2){
	EXPECT_THROW(WordNet WN_ins_2("some_string","any_string") , std::invalid_argument);
	
}


TEST(WordNet_constructor, case_3){
	WordNet WN_ins("synsets.txt", "hypernyms.txt");
}

TEST(WordNet_nouns, case_1){

	WordNet WN_ins("synsets.txt", "hypernyms.txt");


	auto all_words = WN_ins.nouns();
	GTEST_COUT<<"Now print part of the nouns: "<<std::endl;
	int i=0;
	for(auto noun : all_words){
		++i;
		std::cout<< noun<<std::endl;
		if(i==36){break;}
	}

	EXPECT_FALSE(all_words.contains("test_string") );
	EXPECT_TRUE(all_words.contains("'hood") );
	EXPECT_TRUE(all_words.contains("AND_circuit AND_gate") );
}

TEST(WordNet_isNoun, case_2){

	WordNet WN_ins("synsets.txt", "hypernyms.txt");

	EXPECT_FALSE(WN_ins.isNoun("test_string") );
	EXPECT_TRUE(WN_ins.isNoun("'hood"));
	EXPECT_TRUE(WN_ins.isNoun("AND_circuit AND_gate"));

}


int main(int argc, char* argv[]){

	std::cout<< "This script is to test the WordNet head file."
		<< std::endl;

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
