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






int main(int argc, char* argv[]){
    std::cout<< "This file is to test the BaseballElimination.hpp head file"
             <<std::endl;
    
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}

