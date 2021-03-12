#include<iostream>
#include "gtest/gtest.h"



#define private public
    #include "BaseballElimination.hpp"
#undef private

#define GTEST_COUT std::cout<<"[CUSTOM INFO] "
#define GTEST_LINE_HEADER "[          ] "


TEST(BaseballElimination_constructor, case_1){

    BaseballElimination BE_ins{};
}

TEST(BaseballElimination_constructor, case_2){

    std::string filename = "/baseball/teams4.txt";
    BaseballElimination BE_ins(filename);
}

TEST(BaseballElimination_constructor, case_3){

    std::string filename = "/team4.txt";
    EXPECT_THROW (BaseballElimination BE_ins(filename), std::exception );
}


int main(int argc, char* argv[]){
    std::cout<< "This file is to test the BaseballElimination.hpp head file"
             <<std::endl;
    
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}