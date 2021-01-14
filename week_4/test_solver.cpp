#include <iostream>
#include <gtest/gtest.h>
#include <exception>
#include "Solver.hpp"
#define GTEST_COUT std::cout<< "[CUSTOM INFO] "

TEST(Solver, constructor){
	EXPECT_THROW(Solver{}, std::invalid_argument);
	std::vector<int> test_vec={1,2,3,4,5,6,7,8,0};
	Board board_ins(test_vec);
	Solver solver_ins_1(board_ins);

}

TEST(case_1, solution_case_1){

	std::vector<int> test_vec={1,2,3,4,5,6,7,8,0};
	Board board_ins(test_vec);
	Solver solver_ins_1(board_ins);
	auto result=  solver_ins_1.solution();
	for(auto item : result){
		GTEST_COUT<< item.toString() << std::endl;
	}

}


TEST(case_2, solution_case_2){

	std::vector<int> test_vec={1,2,3,4,5,6,7,0,8};
	Board board_ins(test_vec);
	Solver solver_ins_1(board_ins);
	auto result=  solver_ins_1.solution();
	for(auto item : result){
		GTEST_COUT<< item.toString() << std::endl;
	}

}


TEST(case_3, solution_case_3){

	std::vector<int> test_vec={0,1,3,4,2,5,7,8,6};
	Board board_ins(test_vec);
	Solver solver_ins_1(board_ins);
	auto result=  solver_ins_1.solution();
	for(auto item : result){
		GTEST_COUT<< item.toString() << std::endl;
	}

}

TEST(case_4, solution_case_4){

	std::vector<int> test_vec={1,2,3,4,8,6,5,7,0};
	Board board_ins(test_vec);
	Solver solver_ins_1(board_ins);
	auto result=  solver_ins_1.solution();
	for(auto item : result){
		GTEST_COUT<< item.toString() << std::endl;
	}
	if(solver_ins_1.isSolvable()== false){
		GTEST_COUT<< "Unsolvable puzzle"<<std::endl;
	}

}


TEST(case_5, solution_case_5){

	std::vector<int> test_vec={1,2,3,4,5,6,8,7,0};
	Board board_ins(test_vec);
	Solver solver_ins_1(board_ins);
	auto result=  solver_ins_1.solution();
	for(auto item : result){
		GTEST_COUT<< item.toString() << std::endl;
	}
	if(solver_ins_1.isSolvable()== false){
		GTEST_COUT<< "Unsolvable puzzle"<<std::endl;
	}

}

TEST(case_6, solution_case_6){

	std::vector<int> test_vec={8,7,2,1,5,0,4,6,3};
	Board board_ins(test_vec);
	Solver solver_ins_1(board_ins);
	auto result=  solver_ins_1.solution();
	for(auto item : result){
		GTEST_COUT<< item.toString() << std::endl;
	}
	if(solver_ins_1.isSolvable()== false){
		GTEST_COUT<< "Unsolvable puzzle"<<std::endl;
	}
	EXPECT_EQ(21, solver_ins_1.moves());

}

TEST(case_7, solution_case_7){

	std::vector<int> test_vec={5,3,1,4,10,2,8,7,14,13,0,11,6,9,15,12};
	Board board_ins(test_vec);
	Solver solver_ins_1(board_ins);
	auto result=  solver_ins_1.solution();
	for(auto item : result){
		GTEST_COUT<< item.toString() << std::endl;
	}
	if(solver_ins_1.isSolvable()== false){
		GTEST_COUT<< "Unsolvable puzzle"<<std::endl;
	}
	

}

TEST(case_8, solution_case){

	std::vector<int> test_vec={0,1,3,4,2,5,7,8,6};
	Board board_ins(test_vec);
	Solver solver_ins_1(board_ins);
	auto result=  solver_ins_1.solution();
	for(auto item : result){
		GTEST_COUT<< item.toString() << std::endl;
	}
	if(solver_ins_1.isSolvable()== false){
		GTEST_COUT<< "Unsolvable puzzle"<<std::endl;
	}
	EXPECT_EQ(4, solver_ins_1.moves());

}
int main(int argc, char* argv[]){

	std::cout<< "This script is to test the solver head file"
		<< std::endl;
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();

}
