#include <iostream>
#include <gtest/gtest.h>
#include <climits>
#include "Point.hpp"
#define GTEST_COUT std::cout << "[CUSTOM INFO] "

TEST(PointTest, checkConstructor){
    Point point_ins{};
    Point point_ins_2(10, 20);
    GTEST_COUT<<"point_ins_2.x: "<<point_ins_2.x <<std::endl;
    GTEST_COUT<<"point_ins_2.y: "<<point_ins_2.y <<std::endl;
    EXPECT_EQ(10, point_ins_2.x);
    EXPECT_EQ(20, point_ins_2.y);
    
    
}

TEST(PointTest, checkSlopeTo){
    Point point_ins(10,20);
    Point point_ins_ver(10,0);
    Point point_ins_hoz(30,20);
    GTEST_COUT<<"Slope to itself: "<< point_ins.slopeTo(point_ins)<<std::endl;
    GTEST_COUT<<"Slope to vertical point:  "<< point_ins.slopeTo(point_ins_ver)<<std::endl;
    GTEST_COUT<<"Slope to horizontal point:  "<< point_ins.slopeTo(point_ins_hoz)<<std::endl;
    EXPECT_EQ(-DBL_MAX, point_ins.slopeTo(point_ins));
    EXPECT_EQ(DBL_MAX,point_ins.slopeTo(point_ins_ver) );
    EXPECT_EQ(0,point_ins.slopeTo(point_ins_hoz) );
}


int main(int ac, char* av[]){
    std::cout<< "This script is to test the Point head file"
             << std::endl;
    
    ::testing::InitGoogleTest(&ac, av);

    return RUN_ALL_TESTS();

}