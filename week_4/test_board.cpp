#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <exception>
#include "Board.hpp"
#define GTEST_COUT std::cout<< "[CUSTOM INFO] "

TEST(BoardTest, constructor){
	int test_data[3][3]{0,1,2,3,4,5,6,7,8};
	Board board_ins_1{};

	std::vector<int> cor_vec{1,5,2,3,4,6,7,8,0};
        Board board_ins_2(cor_vec);

	std::vector<int> err_vec_1{1,2,3,4,5,6,3,4,3};
	EXPECT_THROW(board_ins_1=Board(err_vec_1), std::invalid_argument);

	std::vector<int> err_vec_2{1,2,3,4,5,6,7,8,9};
	EXPECT_THROW(board_ins_1=Board(err_vec_2), std::invalid_argument);

	std::vector<int> err_vec_3{1,3,3,4,5,6,7,8,8,9,9,10};
	EXPECT_THROW(board_ins_1=Board(err_vec_3), std::invalid_argument);
}

TEST(BoardTest, toSTring){

	std::vector<int> cor_vec{1,5,2,3,4,6,7,8,0};
        Board board_ins_1(cor_vec);
	GTEST_COUT << board_ins_1.toString()<<std::endl;

	std::vector<int> vec_2{1,6,7,5,4,3,2,8,9,10,11,13,12,15,14,0};
	Board board_ins_2(vec_2);
	GTEST_COUT << board_ins_2.toString() << std::endl;

}

TEST(BoardTest,dimension){

	std::vector<int> cor_vec{1,5,2,3,4,6,7,8,0};
        Board board_ins_1(cor_vec);
	EXPECT_EQ(3, board_ins_1.dimension());

	std::vector<int> vec_2{1,6,7,5,4,3,2,8,9,10,11,13,12,15,14,0};
	Board board_ins_2(vec_2);
	EXPECT_EQ(4, board_ins_2.dimension());
}

TEST(BoardTest, hamming){
	
	
	std::vector<int> cor_vec{1,5,2,3,4,6,7,8,0};
        Board board_ins_1(cor_vec);
	EXPECT_EQ(4, board_ins_1.hamming());

	std::vector<int> vec_2{1,6,7,5,4,3,2,8,9,10,11,13,12,15,14,0};
	Board board_ins_2(vec_2);
	EXPECT_EQ(10, board_ins_2.hamming());
}

TEST(BoardTest, manhattan){
	std::vector<int> vec{8,1,3,4,0,2,7,6,5};
	Board board_ins_1(vec);
	EXPECT_EQ(10, board_ins_1.manhattan());
}

TEST(BoardTest, isGoal){
	
	std::vector<int> cor_vec{1,5,2,3,4,6,7,8,0};
        Board board_ins_1(cor_vec);
	EXPECT_FALSE( board_ins_1.isGoal());

	std::vector<int> vec_2{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};
	Board board_ins_2(vec_2);
	EXPECT_EQ(0, board_ins_2.hamming());
	EXPECT_TRUE( board_ins_2.isGoal());
}

TEST(BoardTest, equal){


	std::vector<int> cor_vec{1,5,2,3,4,6,7,8,0};
        Board board_ins_1(cor_vec);
	EXPECT_TRUE( board_ins_1 == board_ins_1);

	std::vector<int> vec_2{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};
	std::vector<int> vec_3{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};
	Board board_ins_2(vec_2);
	Board board_ins_3(vec_2);
	EXPECT_FALSE( board_ins_1 == board_ins_2);
	EXPECT_TRUE( board_ins_2 == board_ins_3);



}

TEST(BoardTest, neighbor){
	
	std::vector<int> cor_vec{1,5,2,3,4,6,7,8,0};
        Board board_ins_1(cor_vec);
	GTEST_COUT<<"The test board is: "<<std::endl;
	GTEST_COUT << board_ins_1.toString()<< std::endl;
	GTEST_COUT << "Its neighbors are: "<<std::endl;


	for(auto item : board_ins_1.neighbors() ){
	 	GTEST_COUT << item.toString()<< std::endl;
	}

        
	std::vector<int> vec_2{1,2,3,4,5,6,7,0,9,10,11,12,13,14,15,8};
	Board board_ins_2(vec_2);

	GTEST_COUT<<"The test board is: "<<std::endl;
	GTEST_COUT << board_ins_2.toString()<< std::endl;
	GTEST_COUT << "Its neighbors are: "<<std::endl;


	for(auto item : board_ins_2.neighbors() ){
	 	GTEST_COUT << item.toString()<< std::endl;
	}
}

TEST(BoardTest, twin){
	
	std::vector<int> cor_vec{1,5,2,3,4,6,7,8,0};
        Board board_ins_1(cor_vec);
	GTEST_COUT<<"The test board is: "<<std::endl;
	GTEST_COUT << board_ins_1.toString()<< std::endl;
	GTEST_COUT << "Its twins are: "<<std::endl;

	for(int i{0}; i<5; ++i){
		Board tmp_board = board_ins_1.twin();
		GTEST_COUT<< tmp_board.toString() << std::endl;
	}

}

int main(int argc, char* argv[]){
	std::cout<< "This script is to test the Board.hpp head file"
		<<std::endl;
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}

