#include <iostream>
#include "gtest/gtest.h"

#include "SAP.hpp"

#define GTEST_COUT std::cout<< "[CUSTOM INFO] "

TEST(SAP_constructor, case_1){
	EXPECT_THROW(SAP S_ins{}, std::invalid_argument);
}

TEST(SAP_constructor, case_2){
}


int main(int argc, char* argv []){

	std::cout<<"This script is to test the SAP head file"<<std::endl;
	
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();

}


