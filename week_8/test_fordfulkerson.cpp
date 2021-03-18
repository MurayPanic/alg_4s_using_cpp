#include <iostream>
#include "gtest/gtest.h"

#define GTEST_COUT std::cout<<"[CUSTOM INFO] "
#define GTEST_LINE_HEADER "[           ] "

#define private public
	#include "FordFulkerson.hpp"
#undef private

TEST(FordFulkerson_constructor,case_1){
	FordFulkerson FF_ins{};

}

TEST(FordFulkerson_constructor_2, case_2){
	FlowNetwork FN_ins(2);
	FlowEdge tmp_edge(0,1,98.0,0.0);
	FN_ins.addEdge(tmp_edge);
	GTEST_COUT<< "The flow network for test is:"
			  <<FN_ins.toString();
	FordFulkerson FF_ins(FN_ins, 0, 1);
	
	GTEST_COUT<<"The final flownetwork is:"
	          << FF_ins.FN_data.toString();


}
TEST(FordFulkerson_constructor_3, case_3){
	FlowNetwork FN_ins(2);
	FlowEdge tmp_edge(1,1,98.0,0.0);
	FN_ins.addEdge(tmp_edge);
	GTEST_COUT<< "The flow network for test is:"
			  <<FN_ins.toString();
	FordFulkerson FF_ins(FN_ins, 0, 1);
	
	GTEST_COUT<<"The final flownetwork is:"
	          << FF_ins.FN_data.toString();

	GTEST_COUT <<"Final value: " <<FF_ins.value()<<std::endl;


}

TEST(FordFulkerson_value, case_1){
	FlowNetwork FN_ins(8,15);
	GTEST_COUT<< "The flow network for test is:"
			  <<FN_ins.toString();
	FordFulkerson FF_ins(FN_ins, 0, 7);
	GTEST_COUT << FF_ins.value()<<std::endl;

	GTEST_COUT<<"The final flownetwork is:"
	          << FF_ins.FN_data.toString();
}

TEST(FordFulkerson_value_2, case_2){
	FlowNetwork FN_ins(8);
	FlowEdge edge01 (0,1,10.0,0.0);
	FN_ins.addEdge(edge01);
	FlowEdge edge03 (0,3,5.0,0.0);
	FN_ins.addEdge(edge03);
	FlowEdge edge05 (0,5,15.0,0.0);
	FN_ins.addEdge(edge05);
	FlowEdge edge12 (1,2,9.0,0.0);
	FN_ins.addEdge(edge12);
	FlowEdge edge14 (1,4,15.0,0.0);
	FN_ins.addEdge(edge14);
	FlowEdge edge13 (1,3,4.0,0.0);
	FN_ins.addEdge(edge13);
	FlowEdge edge24 (2,4,15.0,0.0);
	FN_ins.addEdge(edge24);
	FlowEdge edge34 (3,4,8.0,0.0);
	FN_ins.addEdge(edge34);
	FlowEdge edge35 (3,5,4.0,0.0);
	FN_ins.addEdge(edge35);
	FlowEdge edge63 (6,3,6.0,0.0);
	FN_ins.addEdge(edge63);
    FlowEdge edge46 (4,6,15.0,0.0);
	FN_ins.addEdge(edge46);
	FlowEdge edge56 (5,6,16.0,0.0);
	FN_ins.addEdge(edge56);
	FlowEdge edge27 (2,7,10.0,0.0);
	FN_ins.addEdge(edge27);
	FlowEdge edge47 (4,7,10.0,0.0);
	FN_ins.addEdge(edge47);
	FlowEdge edge67 (6,7,10.0,0.0);
	FN_ins.addEdge(edge67);


	GTEST_COUT<< "The flow network for test is:"
			  <<FN_ins.toString();
	FordFulkerson FF_ins(FN_ins, 0, 7);
	GTEST_COUT << FF_ins.value()<<std::endl;

	GTEST_COUT<<"The final flownetwork is:"
	          << FF_ins.FN_data.toString();
}


int main(int argc, char* argv []){
	std::cout<<"This script is to test the FordFulkerson class"<<std::endl;

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();


}
