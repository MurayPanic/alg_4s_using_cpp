#include <iostream>
#include <gtest/gtest.h>
#include <climits>
#include <algorithm>
#include <vector>
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

TEST (PointTest, basicOperator){
	Point point_ins(10,20);
	Point point_ins_ver(10,0);
	Point point_ins_hoz(30,20);
	Point point_ins_1(20,40);
	Point point_ins_2(30,60);
	EXPECT_TRUE(point_ins_ver<point_ins);
	EXPECT_TRUE(point_ins< point_ins_hoz);
	EXPECT_TRUE(point_ins==point_ins);
	std::vector<Point> point_vec{};
	point_vec.push_back(point_ins);
	point_vec.push_back(point_ins_ver);
	point_vec.push_back(point_ins_hoz);
	point_vec.push_back(point_ins_1);
	point_vec.push_back(point_ins_2);
	GTEST_COUT<<"The original list is: ";
	for(auto item : point_vec){
		std::cout<< item.toString()<<" ";
	}
	std::cout<<std::endl;
	sort(point_vec.begin(), point_vec.end());
	GTEST_COUT<<"The sorted list is: ";
	for(auto item : point_vec){
		std::cout<< item.toString()<<" ";
	}
	std::cout<<std::endl;





}

TEST (PointTest, slopeOrder){
	Point point_ins(10,20);
	Point point_ins_ver(10,0);
	Point point_ins_hoz(30,20);
	Point point_ins_small(15,15);
	EXPECT_FALSE( point_ins.slopeOrder(point_ins_ver, point_ins_hoz ));
	EXPECT_TRUE(point_ins_ver.slopeOrder(point_ins_hoz, point_ins_small));
}

TEST (PointTest, toString){
	Point point_ins(10,20);
	Point point_ins_ver(10,0);
	GTEST_COUT<<"point_ins: "<< point_ins.toString()<< std::endl;
	GTEST_COUT<<"point_ins_ver:"<< point_ins_ver.toString()<<std::endl;
	EXPECT_EQ("(10,20)", point_ins.toString() );
	EXPECT_EQ("(10,0)", point_ins_ver.toString() ); 
}


int main(int ac, char* av[]){
    std::cout<< "This script is to test the Point head file"
             << std::endl;
    
    ::testing::InitGoogleTest(&ac, av);

    return RUN_ALL_TESTS();

}
