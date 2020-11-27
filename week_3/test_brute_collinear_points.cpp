#include<iostream>
#include <gtest/gtest.h>
#include "BruteCollinearPoints.hpp"
#define GTEST_COUT std::cout << "[CUSTOM INFO] "

TEST(BCPTest, Constructor){
        try{
	    BruteCollinearPoints BCP_ins{};
	}
	catch(std::invalid_argument& err){
		GTEST_COUT<<err.what()<<std::endl;	
	}	
	EXPECT_THROW(BruteCollinearPoints(),std::invalid_argument);	
}

int main(int ac, char* av[]){
	std::cout<< "This script is to test the BruteCollinearPoints head file"
		 << std::endl;
	::testing::InitGoogleTest(&ac, av);
	return RUN_ALL_TESTS();
}
