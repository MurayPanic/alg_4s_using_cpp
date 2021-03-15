#include <iostream>
#include "gtest/gtest.h"

#define GTEST_COUT std::cout<<"[CUSTOM INFO] "
#define GTEST_LINE_HEADER "[           ] "

#define private public
	#include "FlowNetwork.hpp"
#undef private


int main(int argc, char* argv []){
	std::cout<<"This script is to test the FlowNetwork class"<<std::endl;

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();


}
