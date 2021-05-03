#include<iostream>
#include "gtest/gtest.h"



#define private public
    #include "FlowEdge.hpp"
#undef private

#define GTEST_COUT std::cout<<"[CUSTOM INFO] "
#define GTEST_LINE_HEADER "[          ] "

TEST(FlowEdge_constructor, case_1){

    FlowEdge FE_ins{};
}

TEST(FlowEdge_constructor, case_2){

    FlowEdge FE_ins(1,2, 199.0, 180.0);
    FlowEdge FE_ins_1(1,2, 199);
    FlowEdge FE_ins_2(1,2, 199);
}

TEST(FlowEdge_constructor, case_3){

    EXPECT_THROW (FlowEdge FE_ins(1,2, 19.0, 180.0), std::invalid_argument);
    EXPECT_THROW (FlowEdge FE_ins(-2,1, 19.0, 180.0), std::invalid_argument);
    EXPECT_THROW (FlowEdge FE_ins(1,-2, 190.0, 180.0), std::invalid_argument);
    EXPECT_THROW (FlowEdge FE_ins(1,-2, 190.0, 180.0), std::invalid_argument);
}

TEST(FlowEdge_constructor, case_4){

	FlowEdge FE_ins(1,2,199.0, 180);
	FlowEdge FE_ins_2(FE_ins);

}

TEST(FlowEdge_assign_operator, case_1){

	FlowEdge FE_ins(1,2,199.0,180.0);
	FlowEdge FE_ins_2 = FE_ins;

}


TEST(FlowEdge_from, case_1){

	FlowEdge FE_ins(1,2,199.0,180.0);
	EXPECT_EQ(FE_ins.from(),1);

}

TEST(FlowEdge_to, case_1){

	FlowEdge FE_ins(1,2,199.0,180.0);
	EXPECT_EQ(FE_ins.to(),2);

}


TEST(FlowEdge_other, case_1){

	FlowEdge FE_ins(1,2,199.0,180.0);
	EXPECT_EQ(FE_ins.other(2),1);
	EXPECT_EQ(FE_ins.other(1),2);

}

TEST(FlowEdge_other, case_2){

	FlowEdge FE_ins(1,2,199.0,180.0);
	EXPECT_THROW(FE_ins.other(3), std::invalid_argument);

}


TEST(FlowEdge_capacity, case_1){

	FlowEdge FE_ins(1,2,199.0,180.0);
	double tmp = FE_ins.capacity() -199.0;
	bool diff = std::abs(tmp) <1E-10;
	EXPECT_TRUE(diff);	

}


TEST(FlowEdge_flow, case_1){

	FlowEdge FE_ins(1,2,199.0,180.0);
	double tmp = FE_ins.flow() -180.0;
	bool diff = std::abs(tmp) <1E-10;
	EXPECT_TRUE(diff);	

}


TEST(FlowEdge_residualCapacityTo, case_1){

	FlowEdge FE_ins(1,2,199.0,180.0);
	double backward_edge_res = FE_ins.residualCapacityTo(1);
	EXPECT_DOUBLE_EQ(backward_edge_res, 180.0);
}

TEST(FlowEdge_residualCapacityTo, case_2){

	FlowEdge FE_ins(1,2,199.0,180.0);
	double backward_edge_res = FE_ins.residualCapacityTo(2);
	EXPECT_DOUBLE_EQ(backward_edge_res, 19.0);
}

TEST(FlowEdge_addResidualFlowTo, case_1){
	

	FlowEdge FE_ins(1,2,199.0,180.0);
	EXPECT_THROW(FE_ins.addResidualFlowTo(1,-99), std::invalid_argument);
}

TEST(FlowEdge_addResidualFlowTo, case_2){
	
	FlowEdge FE_ins(1,2,199.0,180.0);
	FE_ins.addResidualFlowTo(1, 99);
	double backward_edge_res = FE_ins.residualCapacityTo(1);
	EXPECT_DOUBLE_EQ(backward_edge_res, 81.0);

	EXPECT_THROW(FE_ins.addResidualFlowTo(1, 99), std::invalid_argument);
}


TEST(FlowEdge_addResidualFlowTo, case_3){
	
	FlowEdge FE_ins(1,2,199.0,180.0);
	FE_ins.addResidualFlowTo(2, 2);
	double backward_edge_res = FE_ins.residualCapacityTo(1);
	EXPECT_DOUBLE_EQ(backward_edge_res, 182.0);

	double forward_edge_res = FE_ins.residualCapacityTo(2);
	EXPECT_DOUBLE_EQ(forward_edge_res, 17);

	EXPECT_THROW(FE_ins.addResidualFlowTo(2, 99), std::invalid_argument);
}

TEST(FlowEdge_toString, case_1){


	FlowEdge FE_ins(1,2,199.0,180.0);
	GTEST_COUT<< FE_ins.toString()<<std::endl;

}



int main(int argc, char* argv[]){
    std::cout<< "This file is to test the BaseballElimination.hpp head file"
             <<std::endl;
    
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}

