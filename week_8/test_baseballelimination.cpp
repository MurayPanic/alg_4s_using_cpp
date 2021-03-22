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

TEST(BaseballElimination_isEliminated, case_1){
    std::string filename = "/baseball/teams5.txt";
    BaseballElimination BE_ins(filename);
    FlowNetwork FN_data = BE_ins.construct_graph(4);
    GTEST_COUT <<FN_data.toString()<<std::endl;
    std::string team_name="Detroit";
    BE_ins.isEliminated(team_name);
    

}

TEST(BaseballElimination_isEliminated, case_2){
    std::string filename = "/baseball/teams54.txt";
    BaseballElimination BE_ins(filename);
    
    
    std::string team_name="Team3";
    EXPECT_TRUE(BE_ins.isEliminated(team_name));

    team_name="Team29";
    EXPECT_TRUE(BE_ins.isEliminated(team_name));

    team_name="Team37";
    EXPECT_TRUE(BE_ins.isEliminated(team_name));

    team_name="Team50";
    EXPECT_TRUE(BE_ins.isEliminated(team_name));

    team_name="Team6";
    EXPECT_FALSE(BE_ins.isEliminated(team_name));
    

}

TEST(BaseballElimination_isEliminated, case_3){
    std::string filename = "/baseball/teams4.txt";
    BaseballElimination BE_ins(filename);
    
    
    std::string team_name="Philadelphia";
    EXPECT_TRUE(BE_ins.isEliminated(team_name));

    

}

TEST(BaseballElimination_isEliminated, case_4){
    std::string filename = "/baseball/teams4a.txt";
    BaseballElimination BE_ins(filename);
   
    std::string team_name="Ghaddafi";
    EXPECT_TRUE(BE_ins.isEliminated(team_name));

}


TEST(BaseballElimination_isEliminated, case_5){
    std::string filename = "/baseball/teams5.txt";
    BaseballElimination BE_ins(filename);
    
    std::string team_name="Detroit";
    EXPECT_TRUE(BE_ins.isEliminated(team_name));

}

TEST(BaseballElimination_isEliminated, case_6){
    std::string filename = "/baseball/teams7.txt";
    BaseballElimination BE_ins(filename);
    
    std::string team_name="Ireland";
    EXPECT_TRUE(BE_ins.isEliminated(team_name));

}

TEST(BaseballElimination_isEliminated, case_7){
    std::string filename = "/baseball/teams24.txt";
    BaseballElimination BE_ins(filename);
    
    std::string team_name="Team13";
    EXPECT_TRUE(BE_ins.isEliminated(team_name));

}

TEST(BaseballElimination_isEliminated, case_8){
    std::string filename = "/baseball/teams32.txt";
    BaseballElimination BE_ins(filename);
    
    std::string team_name="Team25";
    EXPECT_TRUE(BE_ins.isEliminated(team_name));

    team_name="Team29";
    EXPECT_TRUE(BE_ins.isEliminated(team_name));

    team_name="Team16";
    EXPECT_FALSE(BE_ins.isEliminated(team_name));

}

TEST(BaseballElimination_isEliminated, case_9){
    std::string filename = "/baseball/teams36.txt";
    BaseballElimination BE_ins(filename);
    
    std::string team_name="Team21";
    EXPECT_TRUE(BE_ins.isEliminated(team_name));

}

TEST(BaseballElimination_isEliminated, case_10){
    std::string filename = "/baseball/teams42.txt";
    BaseballElimination BE_ins(filename);
    
   std::string team_name="Team6";
    EXPECT_TRUE(BE_ins.isEliminated(team_name));
    auto certificate = BE_ins.certificateOfElimination(team_name);
    GTEST_COUT<<"The certificate is: "<<std::endl;
    for(auto item : certificate){
        std::cout<< GTEST_LINE_HEADER<< item<<std::endl;
    }


    team_name="Team15";
    EXPECT_TRUE(BE_ins.isEliminated(team_name));

    team_name="Team25";
    EXPECT_TRUE(BE_ins.isEliminated(team_name));

    team_name="Team10";
    EXPECT_FALSE(BE_ins.isEliminated(team_name));

}

TEST(BaseballElimination_isEliminated, case_11){
    std::string filename = "/baseball/teams42.txt";
    BaseballElimination BE_ins(filename);
    
   std::string team_name="Team6";
    EXPECT_TRUE(BE_ins.isEliminated(team_name));

    FlowNetwork  FN_data = BE_ins.construct_graph(6);
    FordFulkerson FF_ins(FN_data, 0, FN_data.V()-1 );
  
  GTEST_COUT<<"Marked : "<<std::endl;
   for(auto i=0; i<42;++i ){
       std::cout<<"Team "<<i <<": "<< FF_ins.marked[861+i]<<std::endl;
   }
     


   

}


TEST(BaseballElimination_isEliminated, case_12){
    std::string filename = "/baseball/teams12.txt";
    BaseballElimination BE_ins(filename);
    
   std::string team_name="Japan";
    EXPECT_TRUE(BE_ins.isEliminated(team_name));

    FlowNetwork  FN_data = BE_ins.construct_graph(6);
    FordFulkerson FF_ins(FN_data, 0, FN_data.V()-1 );
  
  GTEST_COUT<<"Marked : "<<std::endl;
   for(auto i=0; i<42;++i ){
       std::cout<<"Team "<<i <<": "<< FF_ins.marked[861+i]<<std::endl;
   }

   auto result = BE_ins.certificateOfElimination(team_name);
    GTEST_COUT<< "The certificate of elimination:"<< std::endl;
    for (auto item : result){
        std::cout<< GTEST_LINE_HEADER << item <<std::endl;
   }


   

}

TEST(BaseballElimination_isEliminated, case_13){
    std::string filename = "/baseball/teams48.txt";
    BaseballElimination BE_ins(filename);
    
   std::string team_name="Team6";
    EXPECT_TRUE(BE_ins.isEliminated(team_name));

    team_name="Team23";
    EXPECT_TRUE(BE_ins.isEliminated(team_name));

    team_name="Team47";
    EXPECT_TRUE(BE_ins.isEliminated(team_name));

    team_name="Team10";
    EXPECT_FALSE(BE_ins.isEliminated(team_name));

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
