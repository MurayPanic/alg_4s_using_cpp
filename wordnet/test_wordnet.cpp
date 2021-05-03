#include <iostream>
#include <gtest/gtest.h>

# define private public
	#include "WordNet.hpp"
# undef private

#define GTEST_COUT std::cout<< "[CUSTOM INFO] "
#define GTEST_LINE "[           ] "

TEST(WordNet_constructor, case_1){
	WordNet WN_ins{};
}


TEST(WordNet_constructor, case_2){
	EXPECT_THROW(WordNet WN_ins_2("some_string","any_string") , std::invalid_argument);
	
}


TEST(WordNet_constructor, case_3){
	WordNet WN_ins("/wordnet_data/synsets.txt", "/wordnet_data/hypernyms.txt");
}

TEST(WordNet_nouns, case_1){

	WordNet WN_ins("/wordnet_data/synsets.txt", "/wordnet_data/hypernyms.txt");


	auto all_words = WN_ins.nouns();
	GTEST_COUT<<"Now print part of the nouns: "<<std::endl;
	int i=0;
	for(auto noun : all_words){
		++i;
		std::cout<<GTEST_LINE <<noun<<std::endl;
		if(i==36){break;}
	}

	EXPECT_FALSE(all_words.contains("test_string") );
	EXPECT_TRUE(all_words.contains("'hood") );
	EXPECT_TRUE(all_words.contains("AND_circuit") );
	EXPECT_TRUE(all_words.contains("AND_gate") );
}

TEST(WordNet_isNoun, case_2){

	WordNet WN_ins("/wordnet_data/synsets.txt", "/wordnet_data/hypernyms.txt");

	EXPECT_FALSE(WN_ins.isNoun("test_string") );
	EXPECT_TRUE(WN_ins.isNoun("'hood"));
	EXPECT_TRUE(WN_ins.isNoun("AND_circuit") );
	EXPECT_TRUE(WN_ins.isNoun("AND_gate") );
}

TEST(WordNet_distance, case_1){

	WordNet WN_ins("/wordnet_data/synsets.txt", "wordnet_data/hypernyms.txt");
	int result_dist = WN_ins.distance("worm", "bird");
	EXPECT_EQ(result_dist,5);
	
	/*	
	result_dist = WN_ins.distance("white_marlin", "mileage");
	EXPECT_EQ(result_dist, 23);
	

	result_dist = WN_ins.distance("Black_Plague", "black_marlin");
	EXPECT_EQ(result_dist, 33);

	result_dist = WN_ins.distance("American_water_spaniel", "histology");
	EXPECT_EQ(result_dist, 27);
	
	result_dist = WN_ins.distance("Brown_Swiss", "barrel_roll");
	EXPECT_EQ(result_dist, 29);
	*/
}

TEST(WordNet_distance_long, case_2){

	WordNet WN_ins("/wordnet_data/synsets.txt", "/wordnet_data/hypernyms.txt");

	EXPECT_TRUE(WN_ins.isNoun("white_marlin"));
	EXPECT_TRUE(WN_ins.isNoun("mileage"));

	std::string white_marlin_str = "white_marlin";
	std::string mileage_str ="mileage";
	auto white_marlin_num = WN_ins.synset_map_noun_to_num[white_marlin_str];
	auto mileage_num = WN_ins.synset_map_noun_to_num[mileage_str];

	GTEST_COUT<<"The white marlin nums are: ";
	for(auto item : white_marlin_num){
		std::cout<<item<<",";
	}
	std::cout<<std::endl;
	
	GTEST_COUT<<"The mileage nums  are: ";
	for(auto item : mileage_num){
		std::cout<<item<<",";
	}
	std::cout<<std::endl;

	int result_dist = WN_ins.distance(white_marlin_str, mileage_str);
	EXPECT_EQ(result_dist, 23);

	std::vector<int> white_marlin_num_vec{80917};
	std::vector<int> mileage_num_vec{54384,54385,54386};
	int test_dist = WN_ins.sap_ins.length(white_marlin_num_vec, mileage_num_vec);
	EXPECT_EQ(test_dist,23);
}

TEST(WordNet_distance, case_3){

	WordNet WN_ins("/wordnet_data/synsets.txt", "/wordnet_data/hypernyms.txt");

	int result_dist = WN_ins.distance("municipality", "region");
	EXPECT_EQ(result_dist, 3);
	
}

TEST(WordNet_distance, case_4){

	WordNet WN_ins("/wordnet_data/synsets.txt", "/wordnet_data/hypernyms.txt");

	
	int result_dist = WN_ins.distance("Black_Plague", "black_marlin");
	EXPECT_EQ(result_dist, 33);
}

TEST(WordNet_distance, case_5){

	WordNet WN_ins("/wordnet_data/synsets.txt", "/wordnet_data/hypernyms.txt");

	
	int result_dist = WN_ins.distance("American_water_spaniel", "histology");
	EXPECT_EQ(result_dist, 27);
}

TEST(WordNet_distance, case_6){

	WordNet WN_ins("/wordnet_data/synsets.txt", "/wordnet_data/hypernyms.txt");

	
	int result_dist = WN_ins.distance("Brown_Swiss", "barrel_roll");
	EXPECT_EQ(result_dist, 29);
}

TEST(WordNet_sap_long, case_1){

	WordNet WN_ins("/wordnet_data/synsets.txt", "/wordnet_data/hypernyms.txt");

	std::string worm_str="worm";
	std::string bird_str="bird";

	auto worm_num = WN_ins.synset_map_noun_to_num[worm_str];
	auto bird_num = WN_ins.synset_map_noun_to_num[bird_str];

	GTEST_COUT<<"The worm nums are: ";
	for(auto item : worm_num){
		std::cout<<item<<",";
	}
	std::cout<<std::endl;
	
	GTEST_COUT<<"The bird nums  are: ";
	for(auto item : bird_num){
		std::cout<<item<<",";
	}
	std::cout<<std::endl;

	int result_dist = WN_ins.distance(worm_str, bird_str);
	GTEST_COUT<< "Result by distance function is :"<< result_dist<<std::endl;
	EXPECT_EQ(result_dist, 5);

	auto result = WN_ins.sap("worm", "bird");
	GTEST_COUT<< result << std::endl;
	EXPECT_EQ(result,"animal animate_being beast brute creature fauna");

}

TEST(WordNet_sap, case_2){

	WordNet WN_ins("/wordnet_data/synsets.txt", "/wordnet_data/hypernyms.txt");
	auto result = WN_ins.sap("white_marlin","mileage");
	GTEST_COUT<< result << std::endl;
	EXPECT_EQ(result,"entity");

}

TEST(WordNet_sap, case_3){

	WordNet WN_ins("/wordnet_data/synsets.txt", "/wordnet_data/hypernyms.txt");
	auto result = WN_ins.sap("individual","edible_fruit");
	int len = WN_ins.distance("individual","edible_fruit" );
	GTEST_COUT<<"The length between individual and edible_fruit is: "<<len<<std::endl;
	GTEST_COUT<< result << std::endl;
	EXPECT_EQ(result,"physical_entity");

}
int main(int argc, char* argv[]){

	std::cout<< "This script is to test the WordNet head file."
		<< std::endl;

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
