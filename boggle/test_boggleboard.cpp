#include<iostream>
#include "gtest/gtest.h"

#define private public
	#include "BoggleBoard.hpp"
#undef private

#define GTEST_COUT std::cout<<"[CUSTOM INFO] "
#define GTEST_LINE_HEADER "[          ] "

TEST(BoggleBoard_constructor, case_1){

	BoggleBoard BB_ins{};
	
}

TEST(BoggleBoard_constructor, case_2){
	BoggleBoard BB_ins(6,6);
}

TEST(BoggleBoard_consturctor, case_3){
	std::string filename="/boggle/board-q.txt";
	BoggleBoard BB_ins(filename);

}


TEST(BoggleBoard_toString, case_1){
	std::string filename="/boggle/board-q.txt";
	BoggleBoard BB_ins(filename);
	GTEST_COUT<< "The board is :" << std::endl;;
	std::cout<< GTEST_LINE_HEADER << BB_ins.toString();

}

TEST(BoggleBoard_get_Letter, case_1){

	std::string filename="/boggle/board-q.txt";
	BoggleBoard BB_ins(filename);
	auto character = BB_ins.getLetter(0,0);
	EXPECT_EQ(character,'S');
	character = BB_ins.getLetter(2,1);
	EXPECT_EQ(character,'Q');

}

TEST(BoggleBoard_row_and_col, case_1){

	BoggleBoard BB_ins(6,6);
	EXPECT_EQ(BB_ins.rows(),6);
	EXPECT_EQ(BB_ins.cols(),6);
}

TEST(BoggleBoard_row_and_col, case_2){

	std::string filename="/boggle/board-q.txt";
	BoggleBoard BB_ins(filename);
	
	EXPECT_EQ(BB_ins.rows(),4);
	EXPECT_EQ(BB_ins.cols(),4);

}


int main(int argc, char* argv[]){
	std::cout<<"This script is to test the BoggleBoard.hpp head file."
		<< std::endl;

	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();

}
