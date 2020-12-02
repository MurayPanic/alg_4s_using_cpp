#include <iostream>
#include <gtest/gtest.h>
#include "FastCollinearPoints.hpp"
#define GTEST_COUT std::cout << "[CUSTOM INFO] "

TEST(FCPTest, Constructor){
	try {
		FastCollinearPoints FCP_ins{};
	}catch(std::invalid_argument& err){
		GTEST_COUT<< err.what()<<std::endl;
	}
	EXPECT_THROW(FastCollinearPoints(), std::invalid_argument);
}

int main(int ac, char* av[]){
	std::cout<< "This script is to test the FastCollinearPoints head file"
		<<std::endl;
	::testing::InitGoogleTest(&ac, av);
	return RUN_ALL_TESTS();
}
