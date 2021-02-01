#include <iostream>
#include "gtest/gtest.h"
#include <exception>
#include <filesystem>
#include <fstream>

#include "Digraph.hpp"
#define GTEST_COUT std::cout << "[CUSTOM INFO ]"

TEST(Digraph_constructor, case_1){
	Digraph D_ins{};

}

TEST(Digraph_constructor, case_2){
	EXPECT_THROW( Digraph(-1), std::invalid_argument);
}


TEST(Digraph_constructor, case_3){
	Digraph D_ins{3};
	Digraph D_ins_2{20};

}

TEST(Digraph_constructor, case_4){
	std::filesystem::path input_file_path("./tinyDG.txt");
	std::ifstream input_data_flow;
	input_data_flow.open(input_file_path);
	Digraph D_ins(input_data_flow);
}

TEST(Digraph_constructor, case_5){
	std::ifstream input_data_flow;
	EXPECT_THROW( Digraph d_ins(input_data_flow), std::invalid_argument);
}


TEST(Digraph_V_and_E, case_1){
	std::filesystem::path input_file_path("./mediumDG.txt");
	std::ifstream input_data_flow;
	input_data_flow.open(input_file_path);
	Digraph D_ins(input_data_flow);
	EXPECT_EQ(D_ins.V(),50 );
	EXPECT_EQ(D_ins.E(),147);
}

TEST(Digraph_adj,case_1){

	std::filesystem::path input_file_path("./tinyDG.txt");
	std::ifstream input_data_flow;
	input_data_flow.open(input_file_path);
	Digraph D_ins(input_data_flow);
	EXPECT_THROW(D_ins.adj(99), std::invalid_argument );
	EXPECT_THROW(D_ins.adj(-99), std::invalid_argument );
	std::vector<int> adj_1 = D_ins.adj(2);
	GTEST_COUT <<"The adjcent list of 2 is: " ;
	for(auto item : adj_1){
		std::cout<< item<<" ";
	}
	std::cout<<std::endl;
}

TEST(Digraph_indegree, case_1){
	std::filesystem::path input_file_path("./tinyDG.txt");
	std::ifstream input_data_flow;
	input_data_flow.open(input_file_path);
	Digraph D_ins(input_data_flow);

	EXPECT_EQ(D_ins.indegree(2),2);
}

TEST(Digraph_outdegree, case_2){

	std::filesystem::path input_file_path("./tinyDG.txt");
	std::ifstream input_data_flow;
	input_data_flow.open(input_file_path);
	Digraph D_ins(input_data_flow);

	EXPECT_EQ(D_ins.outdegree(2),2);


}

TEST(Digraph_equal_operator, case_1){

	std::filesystem::path input_file_path("./tinyDG.txt");
	std::ifstream input_data_flow;
	input_data_flow.open(input_file_path);
	Digraph D_ins(input_data_flow);

	Digraph D_ins_1;
	D_ins_1 = D_ins;
	Digraph D_ins_2{};
	D_ins_2 = D_ins;
	Digraph D_ins_3=D_ins;


}

TEST(Digraph_reverse, case_1){
	
	std::filesystem::path input_file_path("./tinyDG.txt");
	std::ifstream input_data_flow;
	input_data_flow.open(input_file_path);
	Digraph D_ins(input_data_flow);

	auto reverse_graph = D_ins.reverse();
	GTEST_COUT<<"The reversed graph is: "<< reverse_graph.toString();
	

}

TEST(Digraph_toString, case_1){
	
	std::filesystem::path input_file_path("./tinyDG.txt");
	std::ifstream input_data_flow;
	input_data_flow.open(input_file_path);
	Digraph D_ins(input_data_flow);

	GTEST_COUT<< D_ins.toString();
}


int main(int argc, char* argv[]){
	std::cout<< "This script is to test the Digraph head file"<<std::endl;
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}
