#include <iostream>
#include <filesystem>
#include <fstream>
#include "gtest/gtest.h"

#include "Digraph.hpp"

#define private public
	#include "SAP.hpp"
#undef private

#define GTEST_COUT std::cout<< "[CUSTOM INFO] "
#define GTEST_LINE_HEADER "[           ] "

TEST(SAP_constructor, case_1){

	SAP S_ins{};
}

TEST(SAP_constructor, case_2){
	std::filesystem::path input_file_path("./wordnet_data/digraph1.txt");
	std::ifstream input_data_flow;
	input_data_flow.open(input_file_path);
	Digraph D_ins(input_data_flow);
	
	SAP S_ins(D_ins);

}
/*
TEST(SAP_BreadthFirstSearch, case_1){

	std::filesystem::path input_file_path("./wordnet_data/digraph1.txt");
	std::ifstream input_data_flow;
	input_data_flow.open(input_file_path);
	Digraph D_ins(input_data_flow);
	
	SAP S_ins(D_ins);
	
	std::unordered_set<int> visited_node_list;
	bool found_common_ancestor=false;
	int common_ancestor{-1};
	auto path_table = S_ins.BreadthFirstSearch(9, visited_node_list, found_common_ancestor,common_ancestor);
	EXPECT_FALSE(found_common_ancestor);
	
	GTEST_COUT<< "The visited node list is :" <<std::endl;
	for(auto node : visited_node_list){
		std::cout<< GTEST_LINE_HEADER<< node<< std::endl;
	}
	
	GTEST_COUT<< "The path table is: " << std::endl;
	GTEST_COUT<<"Node  " <<" EdgeTo  "<< " DistTo " <<std::endl;
	GTEST_COUT<<"----------------------------------" << std::endl;

	for (auto path : path_table){
		std::cout<< GTEST_LINE_HEADER << path.first <<": " 
			<< path.second.first <<"   "
			<< path.second.second<<"   "
			<< std::endl;
	}

	GTEST_COUT<<"----------------------------------" << std::endl;
}
*/

TEST(SAP_BreadthFirstSearch, case_1){

	std::filesystem::path input_file_path("./wordnet_data/digraph1.txt");
	std::ifstream input_data_flow;
	input_data_flow.open(input_file_path);
	Digraph D_ins(input_data_flow);
	
	SAP S_ins(D_ins);
	
	bool found_common_ancestor{false};
	std::unordered_set<int> visited_node_list;
	std::unordered_set<int> common_ancestor_list;
	int common_ancestor{-1};

	auto path_table = S_ins.BreadthFirstSearch(9, visited_node_list, common_ancestor_list);
	EXPECT_FALSE(found_common_ancestor);
	
	GTEST_COUT<< "The visited node list is :" <<std::endl;
	for(auto node : visited_node_list){
		std::cout<< GTEST_LINE_HEADER<< node<< std::endl;
	}
	
	GTEST_COUT<< "The path table is: " << std::endl;
	GTEST_COUT<<"Node  " <<" EdgeTo  "<< " DistTo " <<std::endl;
	GTEST_COUT<<"----------------------------------" << std::endl;

	for (auto path : path_table){
		std::cout<< GTEST_LINE_HEADER << path.first <<": " 
			<< path.second.first <<"   "
			<< path.second.second<<"   "
			<< std::endl;
	}

	GTEST_COUT<<"----------------------------------" << std::endl;
}
TEST(SAP_BreadthFirstSearch_MultiSource, case_1){

	std::filesystem::path input_file_path("./wordnet_data/digraph25.txt");
	std::ifstream input_data_flow;
	input_data_flow.open(input_file_path);
	Digraph D_ins(input_data_flow);
	
	SAP S_ins(D_ins);
	
	std::unordered_set<int> visited_node_list;
	std::unordered_set<int> common_ancestor_list;
	std::vector<int> A{13,23,24};
	auto path_table = S_ins.BreadthFirstSearch_MultiSource(A, visited_node_list, common_ancestor_list);
	
	GTEST_COUT<< "The visited node list is :" <<std::endl;
	for(auto node : visited_node_list){
		std::cout<< GTEST_LINE_HEADER<< node<< std::endl;
	}
	
	GTEST_COUT<< "The path table is: " << std::endl;
	GTEST_COUT<<"Node  " <<" EdgeTo  "<< " DistTo " <<std::endl;
	GTEST_COUT<<"----------------------------------" << std::endl;

	for (auto path : path_table){
		std::cout<< GTEST_LINE_HEADER << path.first <<": " 
			<< path.second.first <<"   "
			<< path.second.second<<"   "
			<< std::endl;
	}

	GTEST_COUT<<"----------------------------------" << std::endl;
}


TEST(SAP_length, case_1){

	std::filesystem::path input_file_path("./wordnet_data/digraph1.txt");
	std::ifstream input_data_flow;
	input_data_flow.open(input_file_path);
	Digraph D_ins(input_data_flow);
	
	SAP S_ins(D_ins);

	int len = S_ins.length(3,11);
	EXPECT_EQ(len, 4);

	len = S_ins.length(9,12);
	EXPECT_EQ(len, 3);

	len = S_ins.length(7,2);
	EXPECT_EQ(len, 4);

	len= S_ins.length(1,6);
	EXPECT_EQ(len ,-1);
	

}


TEST(SAP_length, case_2){

	std::filesystem::path input_file_path("./wordnet_data/digraph1.txt");
	std::ifstream input_data_flow;
	input_data_flow.open(input_file_path);
	Digraph D_ins(input_data_flow);
	
	SAP S_ins(D_ins);

	int len = S_ins.length(3,3);
	EXPECT_EQ(len, 0);

	EXPECT_THROW(S_ins.length(3,33), std::invalid_argument);
	EXPECT_THROW(S_ins.length(33,3), std::invalid_argument);
	EXPECT_THROW(S_ins.length(33,34), std::invalid_argument);

	

}




TEST(SAP_ancestor, case_1){

	std::filesystem::path input_file_path("./wordnet_data/digraph1.txt");
	std::ifstream input_data_flow;
	input_data_flow.open(input_file_path);
	Digraph D_ins(input_data_flow);
	
	SAP S_ins(D_ins);

	int result  = S_ins.ancestor(3,3);
	EXPECT_EQ(result, 3);

	result = S_ins.ancestor(9,12);
	EXPECT_EQ(result, 5);

	result = S_ins.ancestor(7,2);
	EXPECT_EQ(result, 0);

	result= S_ins.ancestor(1,6);
	EXPECT_EQ(result ,-1);
}


TEST(SAP_ancestor, case_2){

	std::filesystem::path input_file_path("./wordnet_data/digraph1.txt");
	std::ifstream input_data_flow;
	input_data_flow.open(input_file_path);
	Digraph D_ins(input_data_flow);
	
	SAP S_ins(D_ins);

	int result  = S_ins.ancestor(3,11);
	EXPECT_EQ(result, 1);

	EXPECT_THROW(S_ins.ancestor(3,33), std::invalid_argument);
	EXPECT_THROW(S_ins.ancestor(33,3), std::invalid_argument);
	EXPECT_THROW(S_ins.ancestor(33,34), std::invalid_argument);
}

TEST(SAP_length_set, case_1){
	
	std::filesystem::path input_file_path("./wordnet_data/digraph25.txt");
	std::ifstream input_data_flow;
	input_data_flow.open(input_file_path);
	Digraph D_ins(input_data_flow);
	
	SAP S_ins(D_ins);
	
	std::vector A{13,23,24};
	std::vector B{6,16,17};
	int result_len = S_ins.length(A,B);
	EXPECT_EQ(result_len, 4);

}

TEST(SAP_length_set, case_2){
	
	std::filesystem::path input_file_path("./wordnet_data/digraph25.txt");
	std::ifstream input_data_flow;
	input_data_flow.open(input_file_path);
	Digraph D_ins(input_data_flow);
	
	SAP S_ins(D_ins);
	
	std::vector A{13};
	std::vector B{14};
	int result_len = S_ins.length(A,B);
	EXPECT_EQ(result_len, 2);

}

TEST(SAP_length_set, case_3){
	
	std::filesystem::path input_file_path("./wordnet_data/digraph25.txt");
	std::ifstream input_data_flow;
	input_data_flow.open(input_file_path);
	Digraph D_ins(input_data_flow);
	
	SAP S_ins(D_ins);
	
	std::vector<int> A{8};
	std::vector<int> B;
	B.push_back(17);
	B.push_back(10);
	B.push_back(5);
	B.push_back(2);
	B.push_back(15);
	int result_len = S_ins.length(A,B);
	EXPECT_EQ(result_len, 3);

}

TEST(SAP_length_set, case_4){
	
	std::filesystem::path input_file_path("./wordnet_data/digraph25.txt");
	std::ifstream input_data_flow;
	input_data_flow.open(input_file_path);
	Digraph D_ins(input_data_flow);
	
	SAP S_ins(D_ins);
	
	std::vector A{7};
	std::vector B{7};
	int result_len = S_ins.length(A,B);
	EXPECT_EQ(result_len, 0);

}

TEST(SAP_length_set, case_5){
	
	std::filesystem::path input_file_path("./wordnet_data/digraph1.txt");
	std::ifstream input_data_flow;
	input_data_flow.open(input_file_path);
	Digraph D_ins(input_data_flow);
	
	SAP S_ins(D_ins);
	
	std::vector A{1};
	std::vector B{6};
	int result_len = S_ins.length(A,B);
	EXPECT_EQ(result_len, -1);

}

TEST(SAP_ancestor_set, case_1){
	
	std::filesystem::path input_file_path("./wordnet_data/digraph25.txt");
	std::ifstream input_data_flow;
	input_data_flow.open(input_file_path);
	Digraph D_ins(input_data_flow);
	
	SAP S_ins(D_ins);
	
	std::vector A{13,23,24};
	std::vector B{6,16,17};
	int result_ancestor = S_ins.ancestor(A,B);
	EXPECT_EQ(result_ancestor, 3);

}
	
TEST(SAP_ancestor_set, case_2){
	
	std::filesystem::path input_file_path("./wordnet_data/digraph25.txt");
	std::ifstream input_data_flow;
	input_data_flow.open(input_file_path);
	Digraph D_ins(input_data_flow);
	
	SAP S_ins(D_ins);
	
	std::vector A{7};
	std::vector B{9};
	int result_ancestor = S_ins.ancestor(A,B);
	EXPECT_EQ(result_ancestor, 3);

}

TEST(SAP_ancestor_set, case_3){
	
	std::filesystem::path input_file_path("./wordnet_data/digraph25.txt");
	std::ifstream input_data_flow;
	input_data_flow.open(input_file_path);
	Digraph D_ins(input_data_flow);
	
	SAP S_ins(D_ins);
	
	std::vector A{7};
	std::vector B{7};
	int result_ancestor = S_ins.ancestor(A,B);
	EXPECT_EQ(result_ancestor, 7);

}
int main(int argc, char* argv []){

	std::cout<<"This script is to test the SAP head file"<<std::endl;
	
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();

}

