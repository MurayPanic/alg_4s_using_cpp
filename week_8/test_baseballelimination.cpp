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

TEST(BaseballElimination_construct_graph, case_1){
    std::string filename = "/baseball/teams5.txt";
    BaseballElimination BE_ins(filename);
    FlowNetwork FN_data = BE_ins.construct_graph(4);
    GTEST_COUT <<FN_data.toString()<<std::endl;
}

TEST(BaseballElimination_isElimination, case_1){
    std::string filename = "/baseball/teams5.txt";
    BaseballElimination BE_ins(filename);
    FlowNetwork FN_data = BE_ins.construct_graph(4);
    GTEST_COUT <<FN_data.toString()<<std::endl;
    std::string team_name="Detroit";
    BE_ins.isElimination(team_name);
    

}

TEST(BaseballElimination_isElimination, case_2){
    std::string filename = "/baseball/teams54.txt";
    BaseballElimination BE_ins(filename);
    FlowNetwork FN_data = BE_ins.construct_graph(4);
    
    std::string team_name="Team3";
    EXPECT_TRUE(BE_ins.isElimination(team_name));

    team_name="Team29";
    EXPECT_TRUE(BE_ins.isElimination(team_name));

    team_name="Team37";
    EXPECT_TRUE(BE_ins.isElimination(team_name));

    team_name="Team50";
    EXPECT_TRUE(BE_ins.isElimination(team_name));

    team_name="Team6";
    EXPECT_FALSE(BE_ins.isElimination(team_name));
    

}

TEST(BaseballElimination_certificateOfElimination, case_1){
    std::string filename = "/baseball/teams5.txt";
    BaseballElimination BE_ins(filename);
    FlowNetwork FN_data = BE_ins.construct_graph(4);
    GTEST_COUT <<FN_data.toString()<<std::endl;
    std::string team_name="Detroit";
    auto result = BE_ins.certificateOfElimination(team_name);
    GTEST_COUT<< "The certificate of elimination:"<< std::endl;
    for (auto item : result){
        std::cout<< GTEST_LINE_HEADER << item <<std::endl;
    }
    

}


    


int main(int argc, char* argv[]){
    std::cout<< "This file is to test the BaseballElimination.hpp head file"
             <<std::endl;
    
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}