#include<iostream>
#include "gtest/gtest.h"

#define GTEST_COUT std::cout<<"[CUSTOM INFO] "
#define GTEST_LINE_HEADER "[           ] "

#define private public
	#include "FlowNetwork.hpp"
#undef private


TEST(FlowNetwork_constructor, case_1){
	FlowNetwork FN_ins{};
}

TEST(FlowNetwork_constructor, case_2){
	
	FlowNetwork FN_ins(20);
	EXPECT_THROW(FlowNetwork FN_ins_2(-20), std::invalid_argument);
}

TEST(FlowNetwork_constructor, case_3){
	
	FlowNetwork FN_ins(8,15);
	GTEST_COUT<< FN_ins.toString();
	
}


TEST(FlowNetwork_v, case_1){
	FlowNetwork FN_ins(20);
	EXPECT_EQ(FN_ins.V(), 20);
}

TEST(FlowNetwork_e, case_1){
	FlowNetwork FN_ins(20);
	EXPECT_EQ(FN_ins.E(), 0);
}

TEST(FlowNetwork_validateVertex, case_1){
	FlowNetwork FN_ins(20);
	EXPECT_THROW(FN_ins.validateVertex(20), std::invalid_argument );
	EXPECT_THROW(FN_ins.validateVertex(21), std::invalid_argument );
	EXPECT_THROW(FN_ins.validateVertex(-2), std::invalid_argument );
}


int main(int argc, char* argv[]){

	std::cout<<"This script test the FlowEdge.hpp head file"
		<<std::endl;

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}

