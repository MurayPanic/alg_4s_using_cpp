#include <iostream>
#include <gtest/gtest.h>

#define private public
	#include "Outcast.hpp"
#undef private

#define GTEST_COUT std::cout<< "[CUSTOM INFO] "
#define GTEST_LINE "[          ] "

TEST(Outcast_constructor, case_1){
	Outcast OC_ins{};

}

TEST(Outcast_constructor, cast_2){
	WordNet WN_ins("/wordnet_data/synsets.txt", "/wordnet_data/hypernyms.txt");
	Outcast OC_ins(WN_ins);

}

TEST(Outcast_outcast, case_1){

	WordNet WN_ins("/wordnet_data/synsets.txt", "/wordnet_data/hypernyms.txt");
	Outcast OC_ins(WN_ins);

	std::vector<std::string> nouns{"horse", "zebra", "cat", "bear", "table"};
	auto result=OC_ins.outcast(nouns);
	GTEST_COUT<< "The result is: " <<result <<std::endl;
	EXPECT_EQ(result, "table");

}


TEST(Outcast_outcast_2, case_2){

	WordNet WN_ins("/wordnet_data/synsets.txt", "/wordnet_data/hypernyms.txt");
	Outcast OC_ins(WN_ins);

	std::vector<std::string> nouns{"water", "soda", "bed", "orange_juice", "milk", "apple_juice", "tea", "coffee"};
	auto result=OC_ins.outcast(nouns);
	GTEST_COUT<< "The result is: " <<result <<std::endl;
	EXPECT_EQ(result, "bed");

}

TEST(Outcast_outcast_3, case_3){

	WordNet WN_ins("/wordnet_data/synsets.txt", "/wordnet_data/hypernyms.txt");
	Outcast OC_ins(WN_ins);

	std::vector<std::string> nouns{"apple", "pear", "peach", "banana", "lime", "lemon", "blueberry", "strawberry", "mango", "watermelon", "potato"};
	auto result=OC_ins.outcast(nouns);
	GTEST_COUT<< "The result is: " <<result <<std::endl;
	EXPECT_EQ(result, "potato");

}

int main(int argc, char* argv[]){
	std::cout<< "This script is to test the Outcast.hpp head file."
		<< std::endl;
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}
